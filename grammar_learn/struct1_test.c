#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct Line
{
    uint32_t length;
    // 不占用空间, 柔性数组用法
    // uint8_t contents[];

    // 柔性数组用法
    uint8_t contents[1];
};

int main()
{
    struct Line line;
    int length = 100;

    printf("%ld\n", sizeof(line));

    struct Line *line_ptr = (struct Line *)malloc(sizeof(struct Line) + length);
    // 代表 contents 100 char
    line_ptr->length = 100;

    printf("%ld\n", (int)line_ptr->contents[96]);
    return 0;
}
