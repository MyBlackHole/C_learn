#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define TIMESTRSIZE 1024

static void print_sig(int sig)
{
	// if (sig == SIGINT)
	// {
	//     puts("CTRL+C pressed");
	// }
	write(STDOUT_FILENO, &sig, 4);
}

// 程序结束时调用的析构函数
void __attribute__((destructor)) demo_destructor_func()
{
	printf("%s\n", __FUNCTION__);
}

int demo_SIGKILL_main(void)
{
	time_t stamp;
	struct tm *t_tm;
	char timestr[TIMESTRSIZE];

	// // 无法忽略 SIGKILL
	// signal(SIGKILL, SIG_IGN);
	// 无法捕捉 SIGKILL
	signal(SIGKILL, print_sig);

	printf("pid:%d\n", getpid());

	while (true) {
		stamp = time(NULL);
		t_tm = localtime(&stamp);
		strftime(timestr, TIMESTRSIZE, "NOW:%Y-%m-%d %H:%I:%S", t_tm);
		printf("%s\n", timestr);
		sleep(2);
	}
	printf("Exit main()\n");
}

// output:
// 
// ❯ xmake run signal_learn SIGKILL
// pid:109221
// NOW:2024-10-28 11:11:37
// NOW:2024-10-28 11:11:39
// NOW:2024-10-28 11:11:41
// NOW:2024-10-28 11:11:43
// NOW:2024-10-28 11:11:45
// NOW:2024-10-28 11:11:47
// NOW:2024-10-28 11:11:49
// NOW:2024-10-28 11:11:51
// NOW:2024-10-28 11:11:53
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/signal_learn SIGKILL) failed(-1)
//
//
// kill -9 109221
//
// 尝试 gcc destructo 是否能正常工作 (也不行)
// 
// ❯ xmake run signal_learn SIGKILL
// pid:110408
// NOW:2024-10-28 11:11:28
// NOW:2024-10-28 11:11:30
// NOW:2024-10-28 11:11:32
// NOW:2024-10-28 11:11:34
// NOW:2024-10-28 11:11:36
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/signal_learn SIGKILL) failed(-1)
// 
// ❯ kill -9 110408
