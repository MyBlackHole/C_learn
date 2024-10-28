#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void timeout(int sig) // 信号处理器
{
	if (sig == SIGALRM) {
		puts("Time out!");
	}
	// 为了每隔 2 秒重复产生 SIGALRM 信号
	// 在信号处理器中调用 alarm 函数
	alarm(2);
}

static void keycontrol(int sig) // 信号处理器
{
	if (sig == SIGINT)
		puts("CTRL+C pressed");
}

int demo_signal5_main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM, timeout); // 注册信号及相应处理器
	signal(SIGINT, keycontrol);
	alarm(2); // 预约 2 秒候发生 SIGALRM 信号

	for (i = 0; i < 3; i++) {
		puts("wait...");
		sleep(100);
	}
	return 0;
}
