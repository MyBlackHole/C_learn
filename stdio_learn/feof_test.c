#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int args, char **argv)
{
    FILE *fp;
    int c;

    char *path = dirname(argv[0]);
    char *filename = "/file.txt";
    char *name = malloc(strlen(path) + strlen(filename));

    strcpy(name, path);
    strcat(name, filename);

    fp = fopen(name, "r");
    if (fp == NULL)
    {
        printf("打开文件 file:[%s] 时发生错误", name);
        return (-1);
    }
    while (1)
    {
        c = fgetc(fp);
        if (feof(fp))
        {
            break;
        }
        printf("%c", c);
    }
    fclose(fp);
    return (0);
}
