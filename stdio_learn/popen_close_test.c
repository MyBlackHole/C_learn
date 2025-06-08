#include <stdlib.h>
#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

// 测试 close p_fp 是否会等待子进程结束
// 结论：fclose、pclose 都会等待子进程结束
int demo_popen_close_main(int argc, char *argv[])
{
	FILE *p_fp;
	int ret;

	if (argc != 2) {
		printf("Usage: %s <command>\n", argv[0]);
		return EXIT_FAILURE;
	}

	p_fp = popen(argv[1], "w");
	if (p_fp == NULL) {
		printf("Failed to open pipe\n");
		return EXIT_FAILURE;
	}

	printf("p_fp = %p\n", p_fp);
	printf("close p_fp before waitpid\n");
	ret = pclose(p_fp);
	/*ret = fclose(p_fp);*/
	if (ret == -1) {
		printf("Failed to close pipe\n");
		return EXIT_FAILURE;
	} else {
		printf("pclose return value = %d, exit status = %d\n", ret, WEXITSTATUS(ret));
	}
	
	printf("end of demo_popen_close_main()\n");
	return EXIT_SUCCESS;
}

/*output:(pclose)*/
/**/
/*❯ xmake run stdio_learn popen_close "sleep 10"*/
/*p_fp = 0x584c72b842b0*/
/*close p_fp before waitpid*/
/*pclose return value = 0, exit status = 0*/
/*end of demo_popen_close_main()*/

/*output:(fclose)*/
/*❯ xmake run stdio_learn popen_close "sleep 10"*/
/*p_fp = 0x5e69ed9cd2b0*/
/*close p_fp before waitpid*/
/*pclose return value = 0, exit status = 0*/
/*end of demo_popen_close_main()*/
