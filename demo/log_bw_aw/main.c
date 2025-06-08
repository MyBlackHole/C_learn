#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

/* Log levels */
#define REDIS_DEBUG 0
#define REDIS_VERBOSE 1
#define REDIS_NOTICE 2
#define REDIS_WARNING 3
#define REDIS_LOG_RAW (1 << 10) /* Modifier to log without timestamp */
#define REDIS_DEFAULT_VERBOSITY REDIS_NOTICE
#define REDIS_DEFAULT_SYSLOG_IDENT "redis-syslog"

/* Default maximum length of syslog messages */
#define REDIS_MAX_LOGMSG_LEN 1024

struct server {
	/* Logging */
	char logfile[100]; /* Path of log file */

	// 日志可见性,控制日志打印级别，只有level小于该级别的才会打印，见redisLogRaw
	int verbosity; /* Loglevel in redis.conf */

	int syslog_enabled; /* Is syslog enabled? */
	char *syslog_ident; /* Syslog ident */
	int syslog_facility; /* Syslog facility */
};

struct server server;

/* Low level logging. To use only for very big messages, otherwise
 * redisLog() is to prefer. */
// 如果指定了logfile文件，则输出到logfile，如果没有则在终端打印。同时如果启用了syslog异步日志写，则会输出到syslog指定配置中
// 日志这里是打开文件，写入，然后关闭，这里应该可以优化，只需打开一次即可
void redisLogRaw(int level, const char *msg)
{
	const int syslogLevelMap[] = { LOG_DEBUG, LOG_INFO, LOG_NOTICE,
				       LOG_WARNING };
	const char *c = ".-*#";
	FILE *fp;
	char buf[64];
	int rawmode = (level & REDIS_LOG_RAW);
	// 如果没有设置logfile，则输出到标准输出stdout，否则记录到logfile文件
	int log_to_stdout = server.logfile[0] == '\0';

	level &= 0xff; /* clear flags */

	// 根据日志级别，控制是否需要打印，只有大于等于verbosity的日志级别才会输出
	if (level < server.verbosity) {
		return;
	}

	// 如果没有设置logfile，则输出到标准输出stdout，否则记录到logfile文件
	// 注意是追加方式写入
	fp = log_to_stdout ? stdout : fopen(server.logfile, "a");
	if (!fp) {
		return;
	}

	if (rawmode) {
		fprintf(fp, "%s", msg);
	} else {
		int off;
		struct timeval tv;

		gettimeofday(&tv, NULL);
		off = strftime(buf, sizeof(buf), "%d %b %H:%M:%S.",
			       localtime(&tv.tv_sec));
		snprintf(buf + off, sizeof(buf) - off, "%03d",
			 (int)tv.tv_usec / 1000);
		fprintf(fp, "[%d] %s %c %s\n", (int)getpid(), buf, c[level],
			msg);
	}

	// 落盘
	fflush(fp);

	if (!log_to_stdout) {
		fclose(fp);
	}
	if (server.syslog_enabled) {
		syslog(syslogLevelMap[level], "%s", msg);
	}
}

/* Like redisLogRaw() but with printf-alike support. This is the function that
 * is used across the code. The raw version is only used in order to dump
 * the INFO output on crash. */
void redisLog(int level, const char *fmt, ...)
{
	va_list ap;
	char msg[REDIS_MAX_LOGMSG_LEN];

	if ((level & 0xff) < server.verbosity)
		return;

	va_start(ap, fmt);
	vsnprintf(msg, sizeof(msg), fmt, ap);
	va_end(ap);

	redisLogRaw(level, msg);
}

// 只输出到文件
int main1(int argc, char **argv)
{
	strcpy(server.logfile, "./log");

	server.verbosity = REDIS_NOTICE;

	// 禁用 syslog 异步日志写
	server.syslog_enabled = false;
	// debug 级别低于 notice 级别，不会写入文件
	redisLog(REDIS_DEBUG, "test0,REDIS_DEBUG level output to stdout");
	// warning 级别高于 notice 级别，会写入文件
	redisLog(REDIS_WARNING, "test0,REDIS_WARNING level output to stdout");
	return 0;
}

// 只输出到终端
int main2(int argc, char **argv)
{
	memset(server.logfile, 0, sizeof(server.logfile));

	server.verbosity = REDIS_NOTICE;

	server.syslog_enabled = false;
	// debug 级别低于 notice 级别，不会在终端显示
	redisLog(REDIS_DEBUG, "test1,REDIS_DEBUG level output to stdout");
	// warning 级别高于 notice 级别，会输出到终端
	redisLog(REDIS_WARNING, "test1,REDIS_WARNING level output to stdout");
	return 0;
}

// 输出到文件，并记录到syslog服务日志中。
// 如果日志量很大，同步写文件会严重影响性能，异步syslog写日志可以避免该问题
int main(int argc, char **argv)
{
	strcpy(server.logfile, "./log");

	server.verbosity = REDIS_NOTICE;

	server.syslog_enabled = true;

	// 设置 syslog
	if (server.syslog_enabled) {
		// 2019-06-01T18:22:30.494360+08:00 localhost redis-syslog[24855]:
		// test2,REDIS_WARNING level output to stdout
		// 对应syslog输出中的redis-syslog字符串，同时对应配置文件中的%programname%
		// 见配置文件$template
		// clientlog,"/var/log/testlog/%programname%/log/log.%$
		// ear%%$month%%$day%%$hour%"
		server.syslog_ident = REDIS_DEFAULT_SYSLOG_IDENT;
		// 和配置文件中的local3.* -?clientlog对应
		server.syslog_facility = LOG_LOCAL3;
		openlog(server.syslog_ident, LOG_PID | LOG_NDELAY | LOG_NOWAIT,
			server.syslog_facility);
	}
	// debug级别低于notice级别，不会记录到./log文件和syslog中
	redisLog(REDIS_DEBUG, "test2,REDIS_DEBUG level output to stdout");
	// warning级别高于notice级别，会记录到./log文件和syslog中
	redisLog(REDIS_WARNING, "test2,REDIS_WARNING level output to stdout");
	return 0;
}
