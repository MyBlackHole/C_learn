#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void my_alarm(int signo)
{
	struct passwd *rootptr;
	printf("int the signal function \n");
	if ((rootptr = getpwnam("root")) == NULL) {
		perror("getpwnam(root) error\n");
		exit(1);
	}
	printf("root: %s", rootptr->pw_name);
	alarm(1);
}

int demo_signal4_main(void)
{
	struct passwd *ptr;
	signal(SIGALRM, my_alarm);
	alarm(1);
	for (;;) {
		if ((ptr = getpwnam("black")) == NULL) {
			perror("getpwnam(black) error\n");
			exit(1);
		}
		if (strcmp(ptr->pw_name, "black") != 0) {
			printf("return value corrupted!,pw_name=%s\n",
			       ptr->pw_name);
		}
	}
}
