#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

int demo_uname_test_main(void)
{
	int ret;
	struct utsname myuname;

	ret = uname(&myuname);
	if (ret < 0) {
		perror("uname error");
	} else {
		printf("%s\t%s\t%s\t%s\t%s\n", myuname.sysname,
		       myuname.nodename, myuname.version, myuname.release,
		       myuname.machine);
	}
	//	char buf[64];
	//	if((gethostname(&buf,strlen(buf))<0)
	//		err_sys("gethostname error");
	exit(0);
}
