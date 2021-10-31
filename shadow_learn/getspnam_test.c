#include"apue.h"
#include<shadow.h>


int main(void)
{
	struct spwd *ptr;
	if((ptr=getspnam("black"))==NULL)
		err_sys("getspnam error");
	printf("sp_ pwdp=%s\n",ptr->sp_pwdp==NULL||ptr->sp_pwdp[0]==0? "(null)" : ptr->sp_pwdp);
	exit(0);
}
