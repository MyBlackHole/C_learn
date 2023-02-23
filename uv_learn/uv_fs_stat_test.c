#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

int main(int argc, char *argv[])
{
    struct uv_fs_s req;
    int rv;
    rv = uv_fs_stat(NULL, &req, "/tmp/Test", NULL);
    printf("rv=%d, %s\n", rv, strerror(-rv));
    return EXIT_SUCCESS;
}
