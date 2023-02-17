#include <stdio.h>

int main(void)
{
    char *ptr = "Linux";
    printf("%c\n", *ptr++);
    printf("%c\n", *ptr);
    return 0;
}
