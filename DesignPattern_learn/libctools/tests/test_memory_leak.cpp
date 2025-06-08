#include "mem.h"

auto main() -> int
{
    char *ptr1 = static_cast<char *>(malloc(10));
    int *ptr2 = static_cast<int *>(calloc(10, sizeof(int)));
    auto *ptr3 = static_cast<float *>(calloc(15, sizeof(float)));
    ptr3 = static_cast<float *>(realloc(ptr3, 100 * sizeof(float)));
    (void)ptr1;

    free(ptr1);
    free(ptr2);
    free(ptr3);
    return 0;
}
