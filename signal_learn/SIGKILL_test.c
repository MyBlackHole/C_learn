#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define TIMESTRSIZE 1024

void print_sig(int sig)
{
	// if (sig == SIGINT)
	// {
	//     puts("CTRL+C pressed");
	// }
	write(STDOUT_FILENO, &sig, 4);
}

int main(void)
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
