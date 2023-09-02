#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int demo_opendir_test_main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *dirp;

    if (argc != 2)
    {
        perror("usage: ls directory_name");
    }
    dir = opendir(argv[1]);
    if (dir == NULL)
    {
        fprintf(stderr, "can't open %s", argv[1]);
    }
    while ((dirp = readdir(dir)) != NULL)
    {
        fprintf(stderr, "%s\n", dirp->d_name);
    }

    closedir(dir);
    exit(0);
}
