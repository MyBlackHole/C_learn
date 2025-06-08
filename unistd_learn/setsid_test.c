#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

int demo_setsid_main(int argc, char **argv)
{
	pid_t gpid;
	pid_t old_gpid;
	if (fork() > 0) {
		printf("parent begin\n");
		// for (size_t i = 0; i < 30; i++)
		// {
		//     sleep(1);
		//     printf("parent count:%ld pid:%d\n", i, getpid());
		// }

		printf("parent exit\n");
		/*// 测试 ssh*/
		/*sleep(10);*/
		exit(0);
	}

	/*// 测试 ssh*/
	/*close(0);*/
	/*close(1);*/
	/*close(2);*/

	old_gpid = getpgrp();
	/* 脱离父进程组 */
	gpid = setsid();
	printf("ppid %d, gpid %d---%d\n", getppid(), old_gpid, gpid);

	printf("child begin\n");

	for (size_t i = 0; ; i++) { // 测试 ssh 是否会退出
		sleep(2);
		printf("child count:%ld pid:%d\n", i, getpid());
	}
	/*for (size_t i = 0; i < 10; i++) {*/
	/*	sleep(2);*/
	/*	printf("child count:%ld pid:%d\n", i, getpid());*/
	/*}*/

	printf("child exit\n");
	return 0;
}

// 测试 ssh 是否会退出
// ssh black@127.0.0.1 "/run/media/black/Data/Documents/c/build/linux/x86_64/debug/unistd_learn setsid"
//
// 测试结果：
// ssh 一直在后台运行，不会退出。
//
//
// 测试重定向后是否会退出：
// ssh black@127.0.0.1 "/run/media/black/Data/Documents/c/build/linux/x86_64/debug/unistd_learn setsid > /home/black/1.txt 2>&1"
//
// 结果：
// 会退出。
