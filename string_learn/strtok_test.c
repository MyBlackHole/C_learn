#include <stdio.h>
#include <string.h>

int main()
{
    char str[80] = "This is - www.runoob.com - website";
    // 分割符号
    const char s[2] = "-";
    char *token;

    /* 获取第一个子字符串 */
    token = strtok(str, s);

    /* 继续获取其他的子字符串 */
    while (token != NULL)
    {
        printf("%s\n", token);

        token = strtok(NULL, s);
    }

    return (0);
}
