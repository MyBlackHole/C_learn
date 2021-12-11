#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "apue.h"

static void my_alarm(int signo)
{
	struct passwd * rootptr;
	printf("int the signal function \n");
	if((rootptr=getpwnam("root"))==NULL)
		err_sys("getpwnam(root) error\n");
  printf("root: %s", rootptr->pw_name);
	alarm(1);
}


int main(void)
{
	struct passwd *ptr;
	signal(SIGALRM,my_alarm);
	alarm(1);
	for(;;)
	{
		if((ptr=getpwnam("black"))==NULL)
			err_sys("getpwnam(black) error\n");
		if(strcmp(ptr->pw_name,"black")!=0)
			printf("return value corrupted!,pw_name=%s\n",ptr->pw_name);
	}
}
