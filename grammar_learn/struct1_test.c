#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct Line
{
    uint32_t length;
    // 不占用空间, 柔性数组用法
    uint8_t contents[];
};

int main()
{
    struct Line l;
    printf("%ld\n", sizeof(l));

    int length = 100;
    struct Line *lp = (struct Line *)malloc(sizeof(struct Line) + length);
    // 代表 contents 100 char
    lp->length = 100;
    return 0;
}
