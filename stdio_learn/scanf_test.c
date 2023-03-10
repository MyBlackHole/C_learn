#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a;
    int status;
    printf("请输入数字\n");
    status = scanf("%d", &a);
    assert(status);
    if (!status)
    {
        perror("scanf 失败");
        exit(EXIT_FAILURE);
    }
    printf("%d\n", a);
    printf("status:[%d]\n", status);
    return EXIT_SUCCESS;
}
