// gcc -g basename_demo.c -o basename_demo
//

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char* p;
    // p = basename("htttp://www.youku.com/1.mp4/");
    // p = basename("htttp://www.youku.com/1.mp4/"); //会有段错误
    p = basename("htttp://www.youku.com/1.mp4?start=0&end=90");
    printf("%s\n", p);

    // 这是官网的例子
    char *dirc, *basec, *bname, *dname;
    char* path = "/etc/passwd";

    dirc = strdup(path);
    basec = strdup(path);
    dname = dirname(dirc);
    bname = basename(basec);
    printf("dirname=%s, basename=%s\n", dname, bname);
    free(dirc);
    free(basec);

    return 0;
}