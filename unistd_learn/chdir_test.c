#include"apue.h"
#include<fcntl.h>


int main(void)
{
    // 改变工作目录
	if(chdir("/tmp")<0)
		err_sys("chdir error");

	printf("chdir to /tmp successed\n");

	if(chdir("/tmp/lsp_python.log")<0)
		err_sys("chdir error");
	exit(0);
}
