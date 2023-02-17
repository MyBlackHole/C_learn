#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
    char name[4];
    int age;
} people;

int main(int argc, char **argv)  // map a normal file as shared mem:
{
    int fd, i;
    people *p_map;
    // 以读写方式打开， 没有自动创建
    fd = open(argv[1], O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);

    // 文件大小不能为 0
    // 否则读取异常
    write(fd, "\n", 1);

    p_map = mmap(NULL, sizeof(people) * 10, PROT_READ | PROT_WRITE, MAP_SHARED,
                 fd, 0);
    if (p_map == MAP_FAILED)
    {
        perror(strerror(errno));
        exit(0);
    }

    char c[2];
    for (i = 0; i < 10; i++)
    {
        (*(p_map + i)).age = i;
        sprintf(c, "%d", i);
        memccpy(&(*(p_map + i)).name, &c, sizeof(char), 2);
        printf("name: %s age %d;\n", (*(p_map + i)).name, (*(p_map + i)).age);
    }
    // 解除映射时会把内存数据写回文件，但是不会超出文件大小
    munmap(p_map, sizeof(people) * 10);
}
