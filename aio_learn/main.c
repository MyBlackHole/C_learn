#define _GNU_SOURCE  // O_DIRECT
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <libaio.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int errcode;
    int fd;
    char *buf;
    io_context_t ctx;
    unsigned nr_events = 10;
    struct iocb *iocbpp;

    char *name = "/direct.txt";
    char *path = dirname(argv[0]);
    char *file_path = malloc(strlen(name) + strlen(path));
    strcpy(file_path, path);
    strcat(file_path, name);

    // // 一定要 0 初始化
    // memset(&ctx, 0, sizeof(ctx));
    errcode = io_setup(nr_events, &ctx);
    if (errcode < 0)
    {
        printf("io_setup error::%d:%s\n", errcode, strerror(errcode));
    }
    else
    {
        printf("io_setup success\n");
    }
    fd = open(file_path, O_CREAT | O_DIRECT | O_WRONLY,
              S_IRWXU | S_IRWXG | S_IROTH);
    printf("open:%s\n", strerror(errcode));
    errcode = posix_memalign((void **)&buf, sysconf(_SC_PAGESIZE),
                             sysconf(_SC_PAGESIZE));
    assert(errcode == 0);
    printf("posix_memalign:%s\n", strerror(errcode));
    strcpy(buf, "black hole okkkkkkkkkkkkkk!");

    iocbpp = (struct iocb *)malloc(sizeof(struct iocb));
    memset(iocbpp, 0, sizeof(struct iocb));
    iocbpp[0].data = buf;
    iocbpp[0].aio_lio_opcode = IO_CMD_PWRITE;
    iocbpp[0].aio_reqprio = 0;
    iocbpp[0].aio_fildes = fd;
    iocbpp[0].u.c.buf = buf;
    // 必须 512 对齐
    iocbpp[0].u.c.nbytes = sysconf(_SC_PAGESIZE);
    // 必须 512 对齐
    iocbpp[0].u.c.offset = 0;
    errcode = io_submit(ctx, 1, &iocbpp);
    assert(errcode == 1);
    if (errcode != 1)
    {
        printf("io_submit:%s\n", strerror(-errcode));
    }

    struct io_event events[10];
    struct timespec timeout = {1, 100};
    errcode = io_getevents(ctx, 1, 10, events, &timeout);
    assert(errcode == 1);
    if (errcode != 1)
    {
        printf("io_getevents:%s\n", strerror(-errcode));
    }

    free(iocbpp);

    close(fd);
    errcode = io_destroy(ctx);
    if (errcode < 0)
    {
        printf("io_getevents:%s\n", strerror(-errcode));
    }
    free(file_path);

    return 0;
}