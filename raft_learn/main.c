#include <raft.h>
#include <raft/uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

static int ensureDir(const char *dir)
{
    int rv;
    struct stat sb;
    // 获取目录的属性状态
    rv = stat(dir, &sb);
    if (rv == -1)
    {
        // 不存在目录或文件
        if (errno == ENOENT)
        {
            // 创建目录
            rv = mkdir(dir, 0700);
            if (rv != 0)
            {
                printf("error: create directory '%s': %s", dir,
                       strerror(errno));
                return 1;
            }
        }
        else
        {
            printf("error: stat directory '%s': %s", dir, strerror(errno));
            return 1;
        }
    }
    else
    {
        if ((sb.st_mode & S_IFMT) != S_IFDIR)
        {
            // 不是目录
            printf("error: path '%s' is not a directory", dir);
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    const char *dir = "/tmp/raft_test";
    struct uv_loop_s loop;
    struct raft_uv_transport transport;
    struct raft_io io;
    int rv;

    rv = ensureDir(dir);
    if (rv != 0)
    {
        return rv;
    }

    uv_loop_init(&loop);
    raft_uv_tcp_init(&transport, &loop);
    raft_uv_init(&io, &loop, dir, &transport);
    exit(EXIT_SUCCESS);
}
