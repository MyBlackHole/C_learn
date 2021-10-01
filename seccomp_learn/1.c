#include <stdio.h>
#include <sys/prctl.h>

#include <sys/socket.h>
#include <linux/seccomp.h>


int main() {
	printf("init seccomp");
	prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);

	printf("creating socket");
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	return 0;
}
