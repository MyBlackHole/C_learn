/* Copyright (c) 2020 LiteSpeed Technologies */
/*
 * tut.c is the example program to illustrate lsquic API usage.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/limits.h>

#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>

/*#define EV_STANDALONE 1*/
/*#define EV_API_STATIC 1*/
#include <ev.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include "lsquic.h"

static FILE *s_log_fh;

struct tut {
	/* Common elements needed by both client and server: */
	enum {
		TUT_SERVER = 1 << 0,
	} tut_flags;
	int tut_sock_fd; /* socket */
	ev_io tut_sock_w; /* socket watcher */
	ev_timer tut_timer;
	struct ev_loop *tut_loop;
	lsquic_engine_t *tut_engine;
	struct sockaddr_storage tut_local_sas;
	union {
		struct client {
			ev_io stdin_w; /* stdin watcher */
			struct lsquic_conn *conn;
			size_t sz; /* Size of bytes read is stored here */
			char buf[0x100]; /* Read up to this many bytes */
		} c;
	} tut_u;
};

static void tut_process_conns(struct tut *);

static int tut_log_buf(void *ctx, const char *buf, size_t len)
{
	FILE *out = ctx;
	fwrite(buf, 1, len, out);
	fflush(out);
	return 0;
}
static const struct lsquic_logger_if logger_if = {
	tut_log_buf,
};

static int s_verbose;
static void LOG(const char *fmt, ...)
{
	if (s_verbose) {
		va_list ap;
		fprintf(s_log_fh, "LOG: ");
		va_start(ap, fmt);
		(void)vfprintf(s_log_fh, fmt, ap);
		va_end(ap);
		fprintf(s_log_fh, "\n");
	}
}

static SSL_CTX *s_ssl_ctx;

static int tut_load_cert(const char *cert_file, const char *key_file)
{
	int rv = -1;

	s_ssl_ctx = SSL_CTX_new(TLS_method());
	if (!s_ssl_ctx) {
		LOG("SSL_CTX_new failed");
		goto end;
	}
	SSL_CTX_set_min_proto_version(s_ssl_ctx, TLS1_3_VERSION);
	SSL_CTX_set_max_proto_version(s_ssl_ctx, TLS1_3_VERSION);
	SSL_CTX_set_default_verify_paths(s_ssl_ctx);
	if (1 != SSL_CTX_use_certificate_chain_file(s_ssl_ctx, cert_file)) {
		LOG("SSL_CTX_use_certificate_chain_file failed");
		goto end;
	}
	if (1 != SSL_CTX_use_PrivateKey_file(s_ssl_ctx, key_file,
					     SSL_FILETYPE_PEM)) {
		LOG("SSL_CTX_use_PrivateKey_file failed");
		goto end;
	}
	rv = 0;

end:
	if (rv != 0) {
		if (s_ssl_ctx)
			SSL_CTX_free(s_ssl_ctx);
		s_ssl_ctx = NULL;
	}
	return rv;
}

static SSL_CTX *tut_get_ssl_ctx(void *peer_ctx, const struct sockaddr *local)
{
	return s_ssl_ctx;
}

enum ctl_what {
	CW_SENDADDR = 1 << 0,
	CW_ECN = 1 << 1,
};

static void tut_setup_control_msg(struct msghdr *msg, enum ctl_what cw,
				  const struct lsquic_out_spec *spec,
				  unsigned char *buf, size_t bufsz)
{
	struct cmsghdr *cmsg;
	struct sockaddr_in *local_sa;
	struct sockaddr_in6 *local_sa6;
	struct in_pktinfo info;
	struct in6_pktinfo info6;
	size_t ctl_len;

	msg->msg_control = buf;
	msg->msg_controllen = bufsz;

	/* Need to zero the buffer due to a bug(?) in CMSG_NXTHDR.  See
     * https://stackoverflow.com/questions/27601849/cmsg-nxthdr-returns-null-even-though-there-are-more-cmsghdr-objects
     */
	memset(buf, 0, bufsz);

	ctl_len = 0;
	for (cmsg = CMSG_FIRSTHDR(msg); cw && cmsg;
	     cmsg = CMSG_NXTHDR(msg, cmsg)) {
		if (cw & CW_SENDADDR) {
			if (AF_INET == spec->dest_sa->sa_family) {
				local_sa = (struct sockaddr_in *)spec->local_sa;
				memset(&info, 0, sizeof(info));
				info.ipi_spec_dst = local_sa->sin_addr;
				cmsg->cmsg_level = IPPROTO_IP;
				cmsg->cmsg_type = IP_PKTINFO;
				cmsg->cmsg_len = CMSG_LEN(sizeof(info));
				ctl_len += CMSG_SPACE(sizeof(info));
				memcpy(CMSG_DATA(cmsg), &info, sizeof(info));
			} else {
				local_sa6 =
					(struct sockaddr_in6 *)spec->local_sa;
				memset(&info6, 0, sizeof(info6));
				info6.ipi6_addr = local_sa6->sin6_addr;
				cmsg->cmsg_level = IPPROTO_IPV6;
				cmsg->cmsg_type = IPV6_PKTINFO;
				cmsg->cmsg_len = CMSG_LEN(sizeof(info6));
				memcpy(CMSG_DATA(cmsg), &info6, sizeof(info6));
				ctl_len += CMSG_SPACE(sizeof(info6));
			}
			cw &= ~CW_SENDADDR;
		} else if (cw & CW_ECN) {
			if (AF_INET == spec->dest_sa->sa_family) {
				const int tos = spec->ecn;
				cmsg->cmsg_level = IPPROTO_IP;
				cmsg->cmsg_type = IP_TOS;
				cmsg->cmsg_len = CMSG_LEN(sizeof(tos));
				memcpy(CMSG_DATA(cmsg), &tos, sizeof(tos));
				ctl_len += CMSG_SPACE(sizeof(tos));
			} else {
				const int tos = spec->ecn;
				cmsg->cmsg_level = IPPROTO_IPV6;
				cmsg->cmsg_type = IPV6_TCLASS;
				cmsg->cmsg_len = CMSG_LEN(sizeof(tos));
				memcpy(CMSG_DATA(cmsg), &tos, sizeof(tos));
				ctl_len += CMSG_SPACE(sizeof(tos));
			}
			cw &= ~CW_ECN;
		} else
			assert(0);
	}

	msg->msg_controllen = ctl_len;
}

/* A simple version of ea_packets_out -- does not use ancillary messages */
static int tut_packets_out_v0(void *packets_out_ctx,
			      const struct lsquic_out_spec *specs,
			      unsigned count)
{
	unsigned n;
	int fd, s = 0;
	struct msghdr msg;

	if (0 == count)
		return 0;

	n = 0;
	msg.msg_flags = 0;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	do {
		fd = (int)(uint64_t)specs[n].peer_ctx;
		msg.msg_name = (void *)specs[n].dest_sa;
		msg.msg_namelen = (AF_INET == specs[n].dest_sa->sa_family ?
					   sizeof(struct sockaddr_in) :
					   sizeof(struct sockaddr_in6)),
		msg.msg_iov = specs[n].iov;
		msg.msg_iovlen = specs[n].iovlen;
		s = sendmsg(fd, &msg, 0);
		if (s < 0) {
			LOG("sendmsg failed: %s", strerror(errno));
			break;
		}
		++n;
	} while (n < count);

	if (n < count)
		LOG("could not send all of them"); /* TODO */

	if (n > 0)
		return n;
	else {
		assert(s < 0);
		return -1;
	}
}

/* A more complicated version of ea_packets_out -- this one sets source IP
 * address and ECN.
 */
static int tut_packets_out_v1(void *packets_out_ctx,
			      const struct lsquic_out_spec *specs,
			      unsigned count)
{
	struct tut *const tut = packets_out_ctx;
	unsigned n;
	int fd, s = 0;
	struct msghdr msg;
	enum ctl_what cw;
	union {
		/* cmsg(3) recommends union for proper alignment */
		unsigned char buf[CMSG_SPACE(MAX(sizeof(struct in_pktinfo),
						 sizeof(struct in6_pktinfo))) +
				  CMSG_SPACE(sizeof(int))];
		struct cmsghdr cmsg;
	} ancil;

	if (0 == count)
		return 0;

	n = 0;
	msg.msg_flags = 0;
	do {
		fd = (int)(uint64_t)specs[n].peer_ctx;
		msg.msg_name = (void *)specs[n].dest_sa;
		msg.msg_namelen = (AF_INET == specs[n].dest_sa->sa_family ?
					   sizeof(struct sockaddr_in) :
					   sizeof(struct sockaddr_in6)),
		msg.msg_iov = specs[n].iov;
		msg.msg_iovlen = specs[n].iovlen;

		/* Set up ancillary message */
		if (tut->tut_flags & TUT_SERVER)
			cw = CW_SENDADDR;
		else
			cw = 0;
		if (specs[n].ecn)
			cw |= CW_ECN;
		if (cw)
			tut_setup_control_msg(&msg, cw, &specs[n], ancil.buf,
					      sizeof(ancil.buf));
		else {
			msg.msg_control = NULL;
			msg.msg_controllen = 0;
		}

		s = sendmsg(fd, &msg, 0);
		if (s < 0) {
			LOG("sendmsg failed: %s", strerror(errno));
			break;
		}
		++n;
	} while (n < count);

	if (n < count)
		LOG("could not send all of them"); /* TODO */

	if (n > 0)
		return n;
	else {
		assert(s < 0);
		return -1;
	}
}

static int (*const tut_packets_out[])(void *packets_out_ctx,
				      const struct lsquic_out_spec *specs,
				      unsigned count) = {
	tut_packets_out_v0,
	tut_packets_out_v1,
};

static void tut_usage(const char *argv0)
{
	const char *name;

	name = strchr(argv0, '/');
	if (name)
		++name;
	else
		name = argv0;

	fprintf(stdout,
		"Usage: %s [-c cert -k key] [options] IP port\n"
		"\n"
		"   -c cert.file    Certificate.\n"
		"   -k key.file     Key file.\n"
		"   -f log.file     Log message to this log file.  If not specified, the\n"
		"                     messages are printed to stderr.\n"
		"   -L level        Set library-wide log level.  Defaults to 'warn'.\n"
		"   -l module=level Set log level of specific module.  Several of these\n"
		"                     can be specified via multiple -l flags or by combining\n"
		"                     these with comma, e.g. -l event=debug,conn=info.\n"
		"   -v              Verbose: log program messages as well.\n"
		"   -b VERSION      Use callbacks version VERSION.\n"
		"   -p VERSION      Use packets_out version VERSION.\n"
		"   -w VERSION      Use server write callback version VERSION.\n"
		"   -o opt=val      Set lsquic engine setting to some value, overriding the\n"
		"                     defaults.  For example,\n"
		"                           -o version=ff00001c -o cc_algo=2\n"
		"   -G DIR          Log TLS secrets to a file in directory DIR.\n"
		"   -h              Print this help screen and exit.\n",
		name);
}

static lsquic_conn_ctx_t *tut_client_on_new_conn(void *stream_if_ctx,
						 struct lsquic_conn *conn)
{
	struct tut *const tut = stream_if_ctx;
	tut->tut_u.c.conn = conn;
	LOG("created connection");
	return (void *)tut;
}

static void tut_client_on_hsk_done(lsquic_conn_t *conn,
				   enum lsquic_hsk_status status)
{
	struct tut *const tut = (void *)lsquic_conn_get_ctx(conn);

	switch (status) {
	case LSQ_HSK_OK:
	case LSQ_HSK_RESUMED_OK:
		LOG("handshake successful, start stdin watcher");
		ev_io_start(tut->tut_loop, &tut->tut_u.c.stdin_w);
		break;
	default:
		LOG("handshake failed");
		break;
	}
}

static void tut_client_on_conn_closed(struct lsquic_conn *conn)
{
	struct tut *const tut = (void *)lsquic_conn_get_ctx(conn);

	LOG("client connection closed -- stop reading from socket");
	ev_io_stop(tut->tut_loop, &tut->tut_sock_w);
}

static lsquic_stream_ctx_t *
tut_client_on_new_stream(void *stream_if_ctx, struct lsquic_stream *stream)
{
	struct tut *tut = stream_if_ctx;
	LOG("created new stream, we want to write");
	lsquic_stream_wantwrite(stream, 1);
	/* return tut: we don't have any stream-specific context */
	return (void *)tut;
}

/* Echo whatever comes back from server, no verification */
static void tut_client_on_read_v0(struct lsquic_stream *stream,
				  lsquic_stream_ctx_t *h)
{
	struct tut *tut = (struct tut *)h;
	ssize_t nread;
	unsigned char buf[3];

	nread = lsquic_stream_read(stream, buf, sizeof(buf));
	if (nread > 0) {
		fwrite(buf, 1, nread, stdout);
		fflush(stdout);
	} else if (nread == 0) {
		LOG("read to end-of-stream: close and read from stdin again");
		lsquic_stream_shutdown(stream, 0);
		ev_io_start(tut->tut_loop, &tut->tut_u.c.stdin_w);
	} else {
		LOG("error reading from stream (%s) -- exit loop");
		ev_break(tut->tut_loop, EVBREAK_ONE);
	}
}

static size_t tut_client_readf_v1(void *ctx, const unsigned char *data,
				  size_t len, int fin)
{
	if (len) {
		fwrite(data, 1, len, stdout);
		fflush(stdout);
	}
	return len;
}

/* Same functionality as tut_client_on_read_v0(), but use a readf callback */
static void tut_client_on_read_v1(struct lsquic_stream *stream,
				  lsquic_stream_ctx_t *h)
{
	struct tut *tut = (struct tut *)h;
	ssize_t nread;

	nread = lsquic_stream_readf(stream, tut_client_readf_v1, NULL);
	if (nread == 0) {
		LOG("read to end-of-stream: close and read from stdin again");
		lsquic_stream_shutdown(stream, 0);
		ev_io_start(tut->tut_loop, &tut->tut_u.c.stdin_w);
	} else if (nread < 0) {
		LOG("error reading from stream (%s) -- exit loop");
		ev_break(tut->tut_loop, EVBREAK_ONE);
	}
}

/* Alternatively, pass `stream' to lsquic_stream_readf() and call
 * lsquic_stream_get_ctx() to get struct tut *
 */
struct client_read_v2_ctx {
	struct tut *tut;
	lsquic_stream_t *stream;
};

static size_t tut_client_readf_v2(void *ctx, const unsigned char *data,
				  size_t len, int fin)
{
	struct client_read_v2_ctx *v2ctx = ctx;
	if (len)
		fwrite(data, 1, len, stdout);
	if (fin) {
		fflush(stdout);
		LOG("read to end-of-stream: close and read from stdin again");
		lsquic_stream_shutdown(v2ctx->stream, 0);
		ev_io_start(v2ctx->tut->tut_loop, &v2ctx->tut->tut_u.c.stdin_w);
	}
	return len;
}

/* A bit different from v1: act on fin.  This version saves an extra on_read()
 * call at the cost of some complexity.
 */
static void tut_client_on_read_v2(struct lsquic_stream *stream,
				  lsquic_stream_ctx_t *h)
{
	struct tut *tut = (struct tut *)h;
	ssize_t nread;

	struct client_read_v2_ctx v2ctx = {
		tut,
		stream,
	};
	nread = lsquic_stream_readf(stream, tut_client_readf_v2, &v2ctx);
	if (nread < 0) {
		LOG("error reading from stream (%s) -- exit loop");
		ev_break(tut->tut_loop, EVBREAK_ONE);
	}
}

/* Write out the whole line to stream, shutdown write end, and switch
 * to reading the response.
 */
static void tut_client_on_write(struct lsquic_stream *stream,
				lsquic_stream_ctx_t *h)
{
	lsquic_conn_t *conn;
	struct tut *tut;
	ssize_t nw;

	conn = lsquic_stream_conn(stream);
	tut = (void *)lsquic_conn_get_ctx(conn);

	nw = lsquic_stream_write(stream, tut->tut_u.c.buf, tut->tut_u.c.sz);
	if (nw > 0) {
		tut->tut_u.c.sz -= (size_t)nw;
		if (tut->tut_u.c.sz == 0) {
			LOG("wrote all %zd bytes to stream, switch to reading",
			    (size_t)nw);
			lsquic_stream_shutdown(stream,
					       1); /* This flushes as well */
			lsquic_stream_wantread(stream, 1);
		} else {
			memmove(tut->tut_u.c.buf, tut->tut_u.c.buf + nw,
				tut->tut_u.c.sz);
			LOG("wrote %zd bytes to stream, still have %zd bytes to write",
			    (size_t)nw, tut->tut_u.c.sz);
		}
	} else {
		/* When `on_write()' is called, the library guarantees that at least
         * something can be written.  If not, that's an error whether 0 or -1
         * is returned.
         */
		LOG("stream_write() returned %ld, abort connection", (long)nw);
		lsquic_conn_abort(lsquic_stream_conn(stream));
	}
}

static void tut_client_on_close(struct lsquic_stream *stream,
				lsquic_stream_ctx_t *h)
{
	LOG("stream closed");
}

static void (*const tut_client_on_read[])(lsquic_stream_t *,
					  lsquic_stream_ctx_t *h) = {
	tut_client_on_read_v0,
	tut_client_on_read_v1,
	tut_client_on_read_v2,
};

static struct lsquic_stream_if tut_client_callbacks = {
	.on_new_conn = tut_client_on_new_conn,
	.on_hsk_done = tut_client_on_hsk_done,
	.on_conn_closed = tut_client_on_conn_closed,
	.on_new_stream = tut_client_on_new_stream,
	.on_read = tut_client_on_read_v0,
	.on_write = tut_client_on_write,
	.on_close = tut_client_on_close,
};

static lsquic_conn_ctx_t *tut_server_on_new_conn(void *stream_if_ctx,
						 struct lsquic_conn *conn)
{
	struct tut *const tut = stream_if_ctx;

	LOG("created new connection");
	return (void *)tut; /* Pointer to tut is the connection context */
}

static void tut_server_on_conn_closed(lsquic_conn_t *conn)
{
	LOG("closed connection");
}

struct tut_server_stream_ctx {
	size_t tssc_sz; /* Number of bytes in tsc_buf */
	off_t tssc_off; /* Number of bytes written to stream */
	unsigned char tssc_buf[0x100]; /* Bytes read in from client */
};

static lsquic_stream_ctx_t *
tut_server_on_new_stream(void *stream_if_ctx, struct lsquic_stream *stream)
{
	struct tut_server_stream_ctx *tssc;

	/* Allocate a new buffer per stream.  There is no reason why the echo
     * server could not process several echo streams at the same time.
     */
	tssc = malloc(sizeof(*tssc));
	if (!tssc) {
		LOG("cannot allocate server stream context");
		lsquic_conn_abort(lsquic_stream_conn(stream));
		return NULL;
	}

	tssc->tssc_sz = 0;
	tssc->tssc_off = 0;
	lsquic_stream_wantread(stream, 1);
	LOG("created new echo stream -- want to read");
	return (void *)tssc;
}

static void reverse_string(unsigned char *p, size_t len)
{
	unsigned char *q, tmp;

	q = p + len - 1;
	while (p < q) {
		tmp = *p;
		*p = *q;
		*q = tmp;
		++p;
		--q;
	}
}

/* Read until newline and then echo it back */
static void tut_server_on_read(struct lsquic_stream *stream,
			       lsquic_stream_ctx_t *h)
{
	struct tut_server_stream_ctx *const tssc = (void *)h;
	ssize_t nread;
	unsigned char buf[1];

	nread = lsquic_stream_read(stream, buf, sizeof(buf));
	if (nread > 0) {
		tssc->tssc_buf[tssc->tssc_sz] = buf[0];
		++tssc->tssc_sz;
		if (buf[0] == (unsigned char)'\n' ||
		    tssc->tssc_sz == sizeof(tssc->tssc_buf)) {
			LOG("read newline or filled buffer, switch to writing");
			reverse_string(tssc->tssc_buf,
				       tssc->tssc_sz -
					       (buf[0] == (unsigned char)'\n'));
			lsquic_stream_wantread(stream, 0);
			lsquic_stream_wantwrite(stream, 1);
		}
	} else if (nread == 0) {
		LOG("read EOF");
		lsquic_stream_shutdown(stream, 0);
		if (tssc->tssc_sz)
			lsquic_stream_wantwrite(stream, 1);
	} else {
		/* This should not happen */
		LOG("error reading from stream (errno: %d) -- abort connection",
		    errno);
		lsquic_conn_abort(lsquic_stream_conn(stream));
	}
}

static void tut_server_on_write_v0(struct lsquic_stream *stream,
				   lsquic_stream_ctx_t *h)
{
	struct tut_server_stream_ctx *const tssc = (void *)h;
	ssize_t nw;

	assert(tssc->tssc_sz > 0);
	nw = lsquic_stream_write(stream, tssc->tssc_buf + tssc->tssc_off,
				 tssc->tssc_sz - tssc->tssc_off);
	if (nw > 0) {
		tssc->tssc_off += nw;
		if (tssc->tssc_off == tssc->tssc_sz) {
			LOG("wrote all %zd bytes to stream, close stream",
			    (size_t)nw);
			lsquic_stream_close(stream);
		} else
			LOG("wrote %zd bytes to stream, still have %zd bytes to write",
			    (size_t)nw, tssc->tssc_sz - tssc->tssc_off);
	} else {
		/* When `on_write()' is called, the library guarantees that at least
         * something can be written.  If not, that's an error whether 0 or -1
         * is returned.
         */
		LOG("stream_write() returned %ld, abort connection", (long)nw);
		lsquic_conn_abort(lsquic_stream_conn(stream));
	}
}

static size_t tssc_read(void *ctx, void *buf, size_t count)
{
	struct tut_server_stream_ctx *tssc = ctx;

	if (count > tssc->tssc_sz - tssc->tssc_off)
		count = tssc->tssc_sz - tssc->tssc_off;
	memcpy(buf, tssc->tssc_buf + tssc->tssc_off, count);
	tssc->tssc_off += count;
	return count;
}

static size_t tssc_size(void *ctx)
{
	struct tut_server_stream_ctx *tssc = ctx;
	return tssc->tssc_sz - tssc->tssc_off;
}

/* Same functionality as tut_server_on_write_v0(), but use the "reader"
 * callbacks.  This is most useful when data comes from a different source
 * such as file descriptor.
 */
static void tut_server_on_write_v1(struct lsquic_stream *stream,
				   lsquic_stream_ctx_t *h)
{
	struct tut_server_stream_ctx *const tssc = (void *)h;
	struct lsquic_reader reader = {
		tssc_read,
		tssc_size,
		tssc,
	};
	const size_t left = tssc->tssc_sz;
	ssize_t nw;

	nw = lsquic_stream_writef(stream, &reader);
	if (nw > 0 && tssc->tssc_off == tssc->tssc_sz) {
		LOG("wrote all %zd bytes to stream, close stream", left);
		lsquic_stream_close(stream);
	} else if (nw < 0) {
		LOG("stream_write() returned %ld, abort connection", (long)nw);
		lsquic_conn_abort(lsquic_stream_conn(stream));
	}
}

static void tut_server_on_close(struct lsquic_stream *stream,
				lsquic_stream_ctx_t *h)
{
	struct tut_server_stream_ctx *const tssc = (void *)h;
	free(tssc);
	LOG("stream closed");
}

static void (*const tut_server_on_write[])(lsquic_stream_t *,
					   lsquic_stream_ctx_t *) = {
	tut_server_on_write_v0,
	tut_server_on_write_v1,
};

static struct lsquic_stream_if tut_server_callbacks = {
	.on_new_conn = tut_server_on_new_conn,
	.on_conn_closed = tut_server_on_conn_closed,
	.on_new_stream = tut_server_on_new_stream,
	.on_read = tut_server_on_read,
	.on_write = tut_server_on_write_v0,
	.on_close = tut_server_on_close,
};

/* Read one byte at a time -- when user hits enter, send line to server */
static void tut_read_stdin(EV_P_ ev_io *w, int revents)
{
	struct tut *const tut = w->data;
	ssize_t nr;

	assert(tut->tut_u.c.sz < sizeof(tut->tut_u.c.buf));

	nr = read(w->fd, tut->tut_u.c.buf + tut->tut_u.c.sz, 1);
	if (nr > 0) {
		tut->tut_u.c.sz += nr;
		if (tut->tut_u.c.buf[tut->tut_u.c.sz - 1] == '\n' ||
		    sizeof(tut->tut_u.c.buf) == tut->tut_u.c.sz) {
			LOG("read up to newline (or filled buffer): make new stream");
			lsquic_conn_make_stream(tut->tut_u.c.conn);
			ev_io_stop(tut->tut_loop, w);
			tut_process_conns(tut);
		}
	} else if (nr == 0) {
		LOG("read EOF: stop reading from stdin, close connection");
		ev_io_stop(tut->tut_loop, w);
		ev_io_stop(tut->tut_loop, &tut->tut_u.c.stdin_w);
		lsquic_conn_close(tut->tut_u.c.conn);
		tut_process_conns(tut);
	} else {
		LOG("error reading from stdin: %s", strerror(errno));
		ev_break(tut->tut_loop, EVBREAK_ONE);
	}
}

static int tut_set_nonblocking(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL);
	if (-1 == flags)
		return -1;
	flags |= O_NONBLOCK;
	if (0 != fcntl(fd, F_SETFL, flags))
		return -1;

	return 0;
}

/* ToS is used to get ECN value */
static int tut_set_ecn(int fd, const struct sockaddr *sa)
{
	int on, s;

	on = 1;
	if (AF_INET == sa->sa_family)
		s = setsockopt(fd, IPPROTO_IP, IP_RECVTOS, &on, sizeof(on));
	else
		s = setsockopt(fd, IPPROTO_IPV6, IPV6_RECVTCLASS, &on,
			       sizeof(on));
	if (s != 0)
		perror("setsockopt(ecn)");

	return s;
}

/* Set up the socket to return original destination address in ancillary data */
static int tut_set_origdst(int fd, const struct sockaddr *sa)
{
	int on, s;

	on = 1;
	if (AF_INET == sa->sa_family)
		s = setsockopt(fd, IPPROTO_IP,
#if defined(IP_RECVORIGDSTADDR)
			       IP_RECVORIGDSTADDR,
#else
			       IP_PKTINFO,
#endif
			       &on, sizeof(on));
	else
		s = setsockopt(fd, IPPROTO_IPV6, IPV6_RECVPKTINFO, &on,
			       sizeof(on));

	if (s != 0)
		perror("setsockopt");

	return s;
}

static void tut_timer_expired(EV_P_ ev_timer *timer, int revents)
{
	tut_process_conns(timer->data);
}

static void tut_process_conns(struct tut *tut)
{
	int diff;
	ev_tstamp timeout;

	ev_timer_stop(tut->tut_loop, &tut->tut_timer);
	lsquic_engine_process_conns(tut->tut_engine);

	if (lsquic_engine_earliest_adv_tick(tut->tut_engine, &diff)) {
		if (diff >= LSQUIC_DF_CLOCK_GRANULARITY)
			/* Expected case: convert to seconds */
			timeout = (ev_tstamp)diff / 1000000;
		else if (diff <= 0)
			/* It should not happen often that the next tick is in the past
             * as we just processed connections.  Avoid a busy loop by
             * scheduling an event:
             */
			timeout = 0.0;
		else
			/* Round up to granularity */
			timeout = (ev_tstamp)LSQUIC_DF_CLOCK_GRANULARITY /
				  1000000;
		LOG("converted diff %d usec to %.4lf seconds", diff, timeout);
		ev_timer_init(&tut->tut_timer, tut_timer_expired, timeout, 0.);
		ev_timer_start(tut->tut_loop, &tut->tut_timer);
	}
}

static void tut_proc_ancillary(struct msghdr *msg,
			       struct sockaddr_storage *storage, int *ecn)
{
	const struct in6_pktinfo *in6_pkt;
	struct cmsghdr *cmsg;

	for (cmsg = CMSG_FIRSTHDR(msg); cmsg; cmsg = CMSG_NXTHDR(msg, cmsg)) {
		if (cmsg->cmsg_level == IPPROTO_IP && cmsg->cmsg_type ==
#if defined(IP_RECVORIGDSTADDR)
							      IP_ORIGDSTADDR
#else
							      IP_PKTINFO
#endif
		) {
#if defined(IP_RECVORIGDSTADDR)
			memcpy(storage, CMSG_DATA(cmsg),
			       sizeof(struct sockaddr_in));
#else
			const struct in_pktinfo *in_pkt;
			in_pkt = (void *)CMSG_DATA(cmsg);
			((struct sockaddr_in *)storage)->sin_addr =
				in_pkt->ipi_addr;
#endif
		} else if (cmsg->cmsg_level == IPPROTO_IPV6 &&
			   cmsg->cmsg_type == IPV6_PKTINFO) {
			in6_pkt = (void *)CMSG_DATA(cmsg);
			((struct sockaddr_in6 *)storage)->sin6_addr =
				in6_pkt->ipi6_addr;
		} else if ((cmsg->cmsg_level == IPPROTO_IP &&
			    cmsg->cmsg_type == IP_TOS) ||
			   (cmsg->cmsg_level == IPPROTO_IPV6 &&
			    cmsg->cmsg_type == IPV6_TCLASS)) {
			memcpy(ecn, CMSG_DATA(cmsg), sizeof(*ecn));
			*ecn &= IPTOS_ECN_MASK;
		}
	}
}

#if defined(IP_RECVORIGDSTADDR)
#define DST_MSG_SZ sizeof(struct sockaddr_in)
#else
#define DST_MSG_SZ sizeof(struct in_pktinfo)
#endif

#define ECN_SZ CMSG_SPACE(sizeof(int))

/* Amount of space required for incoming ancillary data */
#define CTL_SZ \
	(CMSG_SPACE(MAX(DST_MSG_SZ, sizeof(struct in6_pktinfo))) + ECN_SZ)

static void tut_read_socket(EV_P_ ev_io *w, int revents)
{
	struct tut *const tut = w->data;
	ssize_t nread;
	int ecn;
	struct sockaddr_storage peer_sas, local_sas;
	unsigned char buf[0x1000];
	struct iovec vec[1] = { { buf, sizeof(buf) } };
	unsigned char ctl_buf[CTL_SZ];

	struct msghdr msg = {
		.msg_name = &peer_sas,
		.msg_namelen = sizeof(peer_sas),
		.msg_iov = vec,
		.msg_iovlen = 1,
		.msg_control = ctl_buf,
		.msg_controllen = sizeof(ctl_buf),
	};
	nread = recvmsg(w->fd, &msg, 0);
	if (-1 == nread) {
		if (!(EAGAIN == errno || EWOULDBLOCK == errno))
			LOG("recvmsg: %s", strerror(errno));
		return;
	}

	local_sas = tut->tut_local_sas;
	ecn = 0;
	tut_proc_ancillary(&msg, &local_sas, &ecn);

	(void)lsquic_engine_packet_in(tut->tut_engine, buf, nread,
				      (struct sockaddr *)&local_sas,
				      (struct sockaddr *)&peer_sas,
				      (void *)(uintptr_t)w->fd, ecn);

	tut_process_conns(tut);
}

/*static void **/
/*keylog_open (void *ctx, lsquic_conn_t *conn)*/
/*{*/
/*    const char *const dir = ctx ? ctx : ".";*/
/*    const lsquic_cid_t *cid;*/
/*    FILE *fh;*/
/*    int sz;*/
/*    unsigned i;*/
/*    char id_str[MAX_CID_LEN * 2 + 1];*/
/*    char path[PATH_MAX];*/
/*    static const char b2c[16] = "0123456789ABCDEF";*/
/**/
/*    cid = lsquic_conn_id(conn);*/
/*    for (i = 0; i < cid->len; ++i)*/
/*    {*/
/*        id_str[i * 2 + 0] = b2c[ cid->idbuf[i] >> 4 ];*/
/*        id_str[i * 2 + 1] = b2c[ cid->idbuf[i] & 0xF ];*/
/*    }*/
/*    id_str[i * 2] = '\0';*/
/*    sz = snprintf(path, sizeof(path), "%s/%s.keys", dir, id_str);*/
/*    if ((size_t) sz >= sizeof(path))*/
/*    {*/
/*        LOG("WARN: %s: file too long", __func__);*/
/*        return NULL;*/
/*    }*/
/*    fh = fopen(path, "wb");*/
/*    if (!fh)*/
/*        LOG("WARN: could not open %s for writing: %s", path, strerror(errno));*/
/*    return fh;*/
/*}*/
/**/
/**/
/*static void*/
/*keylog_log_line (void *handle, const char *line)*/
/*{*/
/*    fputs(line, handle);*/
/*    fputs("\n", handle);*/
/*    fflush(handle);*/
/*}*/
/**/
/**/
/*static void*/
/*keylog_close (void *handle)*/
/*{*/
/*    fclose(handle);*/
/*}*/

/*static const struct lsquic_keylog_if keylog_if =*/
/*{*/
/*    .kli_open       = keylog_open,*/
/*    .kli_log_line   = keylog_log_line,*/
/*    .kli_close      = keylog_close,*/
/*};*/

int main(int argc, char **argv)
{
	struct lsquic_engine_api eapi;
	const char *cert_file = NULL, *key_file = NULL, *val;
	int opt, version_cleared = 0, settings_initialized = 0;
	int packets_out_version = 0;
	socklen_t socklen;
	struct lsquic_engine_settings settings;
	struct tut tut;
	union {
		struct sockaddr sa;
		struct sockaddr_in addr4;
		struct sockaddr_in6 addr6;
	} addr;
	const char *key_log_dir = NULL;
	char errbuf[0x100];

	s_log_fh = stderr;

	if (0 !=
	    lsquic_global_init(LSQUIC_GLOBAL_SERVER | LSQUIC_GLOBAL_CLIENT)) {
		fprintf(stderr, "global initialization failed\n");
		exit(EXIT_FAILURE);
	}

	memset(&tut, 0, sizeof(tut));

	while (opt = getopt(argc, argv, "w:b:c:f:k:l:o:p:G:L:hv"), opt != -1) {
		switch (opt) {
		case 'b':
			tut_client_callbacks.on_read =
				tut_client_on_read[atoi(optarg)];
			break;
		case 'c':
			if (settings_initialized) {
				fprintf(stderr,
					"-c and -k should precede -o flags\n");
				exit(EXIT_FAILURE);
			}
			cert_file = optarg;
			break;
		case 'f':
			s_log_fh = fopen(optarg, "ab");
			if (!s_log_fh) {
				perror("cannot open log file for writing");
				exit(EXIT_FAILURE);
			}
			break;
		case 'k':
			if (settings_initialized) {
				fprintf(stderr,
					"-c and -k should precede -o flags\n");
				exit(EXIT_FAILURE);
			}
			key_file = optarg;
			break;
		case 'l':
			if (0 != lsquic_logger_lopt(optarg)) {
				fprintf(stderr, "error processing -l option\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 'p':
			packets_out_version = atoi(optarg);
			break;
		case 'G':
			key_log_dir = optarg;
			(void)key_log_dir;
			break;
		case 'L':
			if (0 != lsquic_set_log_level(optarg)) {
				fprintf(stderr, "error processing -L option\n");
				exit(EXIT_FAILURE);
			}
			break;
		case 'v':
			++s_verbose;
			break;
		case 'w':
			tut_server_callbacks.on_write =
				tut_server_on_write[atoi(optarg)];
			break;
		case 'o': /* For example: -o version=h3-27 */
			if (!settings_initialized) {
				lsquic_engine_init_settings(
					&settings, cert_file || key_file ?
							   LSENG_SERVER :
							   0);
				settings_initialized = 1;
			}
			val = strchr(optarg, '=');
			if (!val) {
				fprintf(stderr,
					"error processing -o: no equal sign\n");
				exit(EXIT_FAILURE);
			}
			++val;
			if (0 == strncmp(optarg, "version=", val - optarg)) {
				if (!version_cleared) {
					/* Clear all version on first -o version= */
					version_cleared = 1;
					settings.es_versions = 0;
				}
				enum lsquic_version ver =
					lsquic_str2ver(val, strlen(val));
				if ((unsigned)ver < N_LSQVER) {
					settings.es_versions |= 1 << ver;
					break;
				}
				ver = lsquic_alpn2ver(val, strlen(val));
				if ((unsigned)ver < N_LSQVER) {
					settings.es_versions |= 1 << ver;
					break;
				}
				fprintf(stderr, "error: unknown version `%s'\n",
					val);
				exit(EXIT_FAILURE);
			} else if (0 ==
				   strncmp(optarg, "cc_algo=", val - optarg))
				settings.es_cc_algo = atoi(val);
			else if (0 == strncmp(optarg, "ecn=", val - optarg))
				settings.es_ecn = atoi(val);
			/* ...and so on: add more options here as necessary */
			else {
				fprintf(stderr,
					"error: unknown option `%.*s'\n",
					(int)(val - 1 - optarg), optarg);
				exit(EXIT_FAILURE);
			}
			break;
		case 'h':
			tut_usage(argv[0]);
			exit(EXIT_SUCCESS);
			break;
		default:
			exit(EXIT_FAILURE);
			break;
		}
	}

	if (optind + 1 >= argc) {
		LOG("please specify IP address and port number");
		exit(EXIT_FAILURE);
	}

	/* Parse IP address and port number */
	if (inet_pton(AF_INET, argv[optind], &addr.addr4.sin_addr)) {
		addr.addr4.sin_family = AF_INET;
		addr.addr4.sin_port = htons(atoi(argv[optind + 1]));
	} else if (memset(&addr.addr6, 0, sizeof(addr.addr6)),
		   inet_pton(AF_INET6, argv[optind], &addr.addr6.sin6_addr)) {
		addr.addr6.sin6_family = AF_INET6;
		addr.addr6.sin6_port = htons(atoi(argv[optind + 1]));
	} else {
		LOG("`%s' is not a valid IP address", argv[optind]);
		exit(EXIT_FAILURE);
	}

	/* Specifying certificate and key files indicates server mode */
	if (cert_file || key_file) {
		if (!(cert_file && key_file)) {
			LOG("Specify both cert (-c) and key (-k) files");
			exit(EXIT_FAILURE);
		}
		if (0 != tut_load_cert(cert_file, key_file)) {
			LOG("Cannot load certificate");
			exit(EXIT_FAILURE);
		}
		tut.tut_flags |= TUT_SERVER;
	}

	if (!settings_initialized)
		lsquic_engine_init_settings(
			&settings,
			tut.tut_flags & TUT_SERVER ? LSENG_SERVER : 0);

	/* At the time of this writing, using the loss bits extension causes
     * decryption failures in Wireshark.  For the purposes of the demo, we
     * override the default.
     */
	settings.es_ql_bits = 0;

	/* Check settings */
	if (0 != lsquic_engine_check_settings(
			 &settings,
			 tut.tut_flags & TUT_SERVER ? LSENG_SERVER : 0, errbuf,
			 sizeof(errbuf))) {
		LOG("invalid settings: %s", errbuf);
		exit(EXIT_FAILURE);
	}

	/* Initialize event loop */
	tut.tut_loop = EV_DEFAULT;
	tut.tut_sock_fd = socket(addr.sa.sa_family, SOCK_DGRAM, 0);

	/* Set up socket */
	if (tut.tut_sock_fd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if (0 != tut_set_nonblocking(tut.tut_sock_fd)) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
	if (0 != tut_set_ecn(tut.tut_sock_fd, &addr.sa))
		exit(EXIT_FAILURE);
	if (tut.tut_flags & TUT_SERVER)
		if (0 != tut_set_origdst(tut.tut_sock_fd, &addr.sa))
			exit(EXIT_FAILURE);

	if (tut.tut_flags & TUT_SERVER) {
		socklen = sizeof(addr);
		if (0 != bind(tut.tut_sock_fd, &addr.sa, socklen)) {
			perror("bind");
			exit(EXIT_FAILURE);
		}
		memcpy(&tut.tut_local_sas, &addr, sizeof(addr));
	} else {
		tut.tut_local_sas.ss_family = addr.sa.sa_family;
		socklen = sizeof(tut.tut_local_sas);
		if (0 != bind(tut.tut_sock_fd,
			      (struct sockaddr *)&tut.tut_local_sas, socklen)) {
			perror("bind");
			exit(EXIT_FAILURE);
		}
		ev_init(&tut.tut_timer, tut_timer_expired);
	}
	ev_io_init(&tut.tut_sock_w, tut_read_socket, tut.tut_sock_fd, EV_READ);
	ev_io_start(tut.tut_loop, &tut.tut_sock_w);

	/* Initialize logging */
	setvbuf(s_log_fh, NULL, _IOLBF, 0);
	lsquic_logger_init(&logger_if, s_log_fh, LLTS_HHMMSSUS);

	/* Initialize callbacks */
	memset(&eapi, 0, sizeof(eapi));
	eapi.ea_packets_out = tut_packets_out[packets_out_version];
	eapi.ea_packets_out_ctx = &tut;
	eapi.ea_stream_if = tut.tut_flags & TUT_SERVER ? &tut_server_callbacks :
							 &tut_client_callbacks;
	eapi.ea_stream_if_ctx = &tut;
	eapi.ea_get_ssl_ctx = tut_get_ssl_ctx;
	/*if (key_log_dir)*/
	/*{*/
	/*    eapi.ea_keylog_if = &keylog_if;*/
	/*    eapi.ea_keylog_ctx = (void *) key_log_dir;*/
	/*}*/
	eapi.ea_settings = &settings;

	tut.tut_engine = lsquic_engine_new(
		tut.tut_flags & TUT_SERVER ? LSENG_SERVER : 0, &eapi);
	if (!tut.tut_engine) {
		LOG("cannot create engine");
		exit(EXIT_FAILURE);
	}

	tut.tut_timer.data = &tut;
	tut.tut_sock_w.data = &tut;
	if (!(tut.tut_flags & TUT_SERVER)) {
		if (0 != tut_set_nonblocking(STDIN_FILENO)) {
			perror("fcntl(stdin)");
			exit(EXIT_FAILURE);
		}
		ev_io_init(&tut.tut_u.c.stdin_w, tut_read_stdin, STDIN_FILENO,
			   EV_READ);
		tut.tut_u.c.stdin_w.data = &tut;
		tut.tut_u.c.conn = lsquic_engine_connect(
			tut.tut_engine, N_LSQVER,
			(struct sockaddr *)&tut.tut_local_sas, &addr.sa,
			(void *)(uintptr_t)tut.tut_sock_fd, /* Peer ctx */
			NULL, NULL, 0, NULL, 0, NULL, 0);
		if (!tut.tut_u.c.conn) {
			LOG("cannot create connection");
			exit(EXIT_FAILURE);
		}
		tut_process_conns(&tut);
	}
	ev_run(tut.tut_loop, 0);

	lsquic_engine_destroy(tut.tut_engine);
	lsquic_global_cleanup();
	exit(EXIT_SUCCESS);
}
