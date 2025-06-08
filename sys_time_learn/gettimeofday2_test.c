#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

// 对于linux下的适配，取消了对于macos 和 solaris
unsigned long long count;
struct timeval end;

void checktime(char *str)
{
	struct timeval tv_tmp;
	gettimeofday(&tv_tmp, NULL);
	if (tv_tmp.tv_sec >= end.tv_sec && tv_tmp.tv_usec >= end.tv_usec) {
		printf("%s\t count=\t%lld \n", str, count);
		exit(0);
	}
}

int demo_gettimeofday2_main(int argc, char **argv)
{
	pid_t pid;
	char *s_tmp;
	int nzero, ret;
	int adj = 0;
	setbuf(stdout, NULL); // 设置缓冲区
#if defined(NZERO)
	nzero = NZERO;
#elif defined(_SC_NZERO)
	nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
	printf("NZERO=%d \n", nzero);
	if (argc == 2) {
		adj = strtol(argv[1], NULL, 10);
	}

	// 提供更精准的时间获取，虽然在susv系统内被舍弃
	gettimeofday(&end, NULL);
	end.tv_sec += 10;

	if ((pid = fork()) < 0) {
		perror("fork error");
		exit(1);
	} else if (pid == 0) {
		s_tmp = "child";
		printf("current nice value in child is %d ,adjusting by %d \n",
		       nice(0) + nzero, adj);
		errno = 0;
		if ((ret = nice(adj)) == -1 && errno != 0) {
			perror("child set scheduling priority");
			exit(1);
		}
		printf("now child nice valude is %d \n", ret + nzero);
	} else {
		s_tmp = "parent";
		printf("current nice value in parent is %d\n", nice(0) + nzero);
	}
	for (;;) {
		if (++count == 0) {
			printf("%s counter wrap", s_tmp);
		}
		checktime(s_tmp);
	}
}
