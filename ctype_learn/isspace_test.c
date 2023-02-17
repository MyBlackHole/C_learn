#include <ctype.h>
#include <stdio.h>

/* 返回值为非零（真）表示c是空白符，返回值为零（假）表示c不是空白符 */
/*
 *  空白符
 *  ' ', '\t', '\v', '\f', '\r'
 */

void func1()
{
    char c;
    int i = 0;
    char str[] = "Example sentence to test isspace\n";
    while (str[i])
    {
        c = str[i];
        if (isspace(c))
        {
            c = '\n';
        }
        putchar(c);
        i++;
    }
}

int main()
{
    func1();
    return 0;
}
