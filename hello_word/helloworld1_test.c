#include"apue.h"


// argv：命令参数 envp：软件运行环境变量
int main(int argc,char **argv,char ** envp)
{
	int i;
	for(i=0;i<argc;++i)
		printf("argv[%d]:%s\n",i,argv[i]);
	for(i=0;envp[i]!=NULL;i++)
		printf("envp[%d]:%s\n",i,envp[i]);
	exit(0);
}

