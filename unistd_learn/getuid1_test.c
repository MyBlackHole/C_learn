#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024

int demo_getuid1_main(int argc, char *argv[])
{
	int fd_in;
	ssize_t len;
	int ret;
	char buf[BUFSIZE + 1] = { 0 };

	// 这三个uid分别是实际用户ID，有效用户ID，保存的设置用户ID
	uid_t ruid;
	uid_t euid;
	uid_t suid;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <root file> \n", argv[0]);
		exit(1);
	}

	printf(" UID\t= %d\n", getuid());
	printf(" EUID\t= %d\n", geteuid());
	printf(" GID\t= %d\n", getgid());
	printf(" EGID\t= %d\n", getegid());

	ret = getresuid(&ruid, &euid, &suid);
	if (ret < 0) {
		perror("getresuid()");
		exit(EXIT_FAILURE);
	}
	printf("real:%d\teffective:%d\tset-user-id:%d\n", ruid, euid, suid);

	// ret = seteuid(0);
	// if (ret < 0)
	// {
	//     perror("setuid()");
	//     exit(EXIT_FAILURE);
	// }

	printf("setuid UID\t= %d\n", getuid());
	printf("setuid EUID\t= %d\n", geteuid());
	printf("setuid GID\t= %d\n", getgid());
	printf("setuid EGID\t= %d\n", getegid());

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in <= 0) {
		perror("open()");
		exit(EXIT_FAILURE);
	}

	len = read(fd_in, buf, BUFSIZE);
	if (len < 0) {
		perror("read()");
		exit(EXIT_FAILURE);
	}

	buf[len] = '\0';
	printf("%s\n", buf);

	return EXIT_SUCCESS;
}
