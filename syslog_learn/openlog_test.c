#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#define SYSNAME "wohawoha"

void Info(void)
{
	/*注意这里的数字5与第一条里面提到的local5.*里的5必须相同，并且这个数字的范围为0--7*/
	openlog("info", LOG_PID, LOG_LOCAL5);
	syslog(LOG_INFO, "hello %s", "woring");
}

void Woring(void)
{
	openlog("woring", LOG_PID, LOG_LOCAL5);
	syslog(LOG_WARNING, "hello %s", "test");
}

// sudo nvim /etc/rsyslog.d/user.conf
// local5.* /var/log/openlog_test
// systemctl restart rsyslog.service
// LOG_LOCAL5
int main()
{
	Info();
	Woring();
	closelog();
	return 0;
}
