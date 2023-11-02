#include <fcntl.h>
#include <libgen.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 4096

struct point
{
    int64_t a;
    int32_t b;
};

typedef struct point point_t;

int main(int argc, char *argv[])
{
    size_t n;
    point_t tr;
    point_t tw;

    char *name = "/write_read_struct_test.bin";
    char *path = dirname(argv[0]);
    char *file_path = malloc(strlen(name) + strlen(path));
    strcpy(file_path, path);
    strcat(file_path, name);

    int fd;

    fd = open(file_path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    // write test
    tw.a = 1000;
    tw.b = 1111;
    n = write(fd, &tw, sizeof(tw));
    if (n != sizeof(tw))
    {
        perror("write error");
        exit(EXIT_FAILURE);
    }

    lseek(fd, 0, SEEK_SET);

    // read test
    n = read(fd, &tr, sizeof(tr));
    if (n != sizeof(tr))
    {
        perror("read error");
        exit(EXIT_FAILURE);
    }

    printf("%d - %d\n", tr.b, n);

    free(file_path);
    exit(EXIT_SUCCESS);
}
