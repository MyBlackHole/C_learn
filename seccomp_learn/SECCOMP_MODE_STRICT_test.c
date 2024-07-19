#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>

// #include <linux/seccomp.h>
#include <seccomp.h>
#include <sys/socket.h>

int demo_STRICT_main()
{
	int err;
	printf("init seccomp\n");
	// 限制系统调用 模式设置为 STRICT
	err = prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);

	printf("%d\n", err);
	if (err < 0) {
		perror(strerror(errno));
	}

	printf("creating socket\n");
	// 异常退出
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror(strerror(errno));
	}

	return 0;
}
