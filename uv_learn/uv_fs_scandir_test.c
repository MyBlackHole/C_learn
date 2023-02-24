#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

int main(int argc, char *argv[])
{
    struct uv_fs_s req;
    struct uv_dirent_s entry;
    int n;
    int rv;

    n = uv_fs_scandir(NULL, &req, "/tmp", 0, NULL);
    for (int i = 0; i < n; i++)
    {
        const char *filename;
        rv = uv_fs_scandir_next(&req, &entry);
        assert(rv == 0); /* Can't fail in libuv */

        filename = entry.name;
        printf("%s\n", filename);
    }
    return EXIT_SUCCESS;
}
