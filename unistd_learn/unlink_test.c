#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 删除文件(引用次数为零时)
int demo_unlink_main(int argc, char **argv)
{
    if (open("tempfile", O_RDWR) < 0)
    {
        perror("open tempfile file faied");
        exit(EXIT_FAILURE);
    }
    if (unlink("tempfile") < 0)
    {
        perror("unlink error");
        exit(EXIT_FAILURE);
    }
    printf("file unlinked \n");
    sleep(10);
    printf("done\n");
    exit(EXIT_SUCCESS);
}
