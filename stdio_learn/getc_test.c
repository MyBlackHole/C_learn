#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c;
    // 获取stdin流输入字符 回车结束
    while ((c = getc(stdin)) != EOF)
    {
        // 写入流字符
        if (putc(c, stdout) == EOF)
        {
            perror("output error");
            exit(1);
        }
    }
    if (ferror(stdin))
    {
        perror("input error");
        exit(1);
    }
    exit(0);
}
