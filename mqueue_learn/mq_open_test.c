#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int demo_mq_open_main(int argc, char *argv[])
{
	int flag = O_RDWR | O_CREAT | O_EXCL;
	int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	mqd_t mqid = mq_open("/mq_test", flag, mode, NULL);
	if (mqid == -1) {
		printf("mqueue create failed!\n");
		return 1;
	} else {
		printf("mqueue create success!\n");
	}
	mq_close(mqid);
	return 0;
}
