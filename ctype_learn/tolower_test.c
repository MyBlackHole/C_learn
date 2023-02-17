#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 大写转小写
 */
int main(int argc, char *argv[])
{
    int i;
    char string[] = "BLACK HOLE;";
    printf("%s\n", string);
    for (i = 0; i < strlen(string); i++)
    {
        putchar(tolower(string[i]));
    }
    printf("\n");
    exit(0);
}
