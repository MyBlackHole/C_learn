#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char str[] = "This is runoob.com";
    char *name = "/file.txt";
    char *path = dirname(argv[0]);
    char *file_path = malloc(strlen(name) + strlen(path));
    strcpy(file_path, path);
    strncat(file_path, name, strlen(name));

    printf("%s\n", file_path);
    fp = fopen(file_path, "w");
    fwrite(str, sizeof(str), 1, fp);

    fclose(fp);

    free(file_path);

    return (0);
}
