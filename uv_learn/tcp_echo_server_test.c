#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128

extern uv_loop_t *loop;
struct sockaddr_in addr;

typedef struct {
	uv_write_t req;
	uv_buf_t buf;
} write_req_t;

extern void free_write_req(uv_write_t *req);

extern void alloc_buffer(uv_handle_t *handle, size_t suggested_size,
			 uv_buf_t *buf);

extern void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);

extern void on_new_connection(uv_stream_t *server, int status);

// nc 127.0.0.1 7000
int demo_tcp_echo_server_main()
{
	loop = uv_default_loop();

	uv_tcp_t server;
	uv_tcp_init(loop, &server);

	uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);

	uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
	int ret = uv_listen((uv_stream_t *)&server, DEFAULT_BACKLOG,
			    on_new_connection);
	if (ret) {
		fprintf(stderr, "Listen error %s\n", uv_strerror(ret));
		return 1;
	}
	return uv_run(loop, UV_RUN_DEFAULT);
}
