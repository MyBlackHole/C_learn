#include"apue.h"
#include <stdio.h>


int main(void)
{
	int c;
    // 获取stdin流输入字符 回车结束
	while((c=getc(stdin))!=EOF)
	{
        // 写入流字符
		if(putc(c,stdout)==EOF)
			err_sys("output error");
	}
	if(ferror(stdin))
		err_sys("input error");
	exit(0);
}
