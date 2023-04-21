#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int main(int argc, char** argv)
{
    int ret;
    char* work_path = dirname(argv[0]);
    ret = chdir(work_path);
    if (ret != 0)
    {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // 设置mask 返回旧的mask
    umask(0);
    if (creat("foo.log", RWRWRW) < 0)
    {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }

    umask(S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH);
    if (creat("bar.log", RWRWRW) < 0)
    {
        perror(strerror(errno));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
