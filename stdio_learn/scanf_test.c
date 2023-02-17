#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a;
    int status;
    printf("请输入数字\n");
    status = scanf("%d", &a);
    printf("%d\n", a);
    printf("status:[%d]\n", status);
    return 0;
}
