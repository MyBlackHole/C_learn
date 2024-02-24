#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Line
{
    uint32_t length;

    // 以下两属性共用内存空间
    uint8_t contents[0];
    uint8_t data[];
};

int demo_struct2_main()
{
    struct Line line;
    int length = 100;

    printf("%ld\n", sizeof(line));

    struct Line *line_ptr = (struct Line *)malloc(sizeof(struct Line) + length);
    // 代表 contents 100 char
    line_ptr->length = 100;
    line_ptr->contents[96] = 100;
    printf("contents: %d\n", line_ptr->contents[96]);
    printf("data: %d\n", line_ptr->data[96]);
    return EXIT_SUCCESS;
}

// out:
// 4
// contents: 100
// data: 100
