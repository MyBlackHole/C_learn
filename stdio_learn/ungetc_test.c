#include <stdio.h>

int main()
{
    FILE *fp;
    int c;
    char buffer[256];

    fp = fopen("file.txt", "r");
    if (fp == NULL)
    {
        perror("打开文件时发生错误");
        return (-1);
    }
    while (!feof(fp))
    {
        c = getc(fp);
        /* 把 ! 替换为 + */
        if (c == '!')
        {
            ungetc('+', fp);
        }
        else
        {
            ungetc(c, fp);
        }
        fgets(buffer, 255, fp);
        fputs(buffer, stdout);
    }
    return (0);
}
