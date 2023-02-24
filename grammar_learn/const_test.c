#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int const num = 1;
    // const int num = 1;
    // num = 3;
    int *p = (int *)&num;
    *p = 2;
    printf("num = %d\n", num);
    printf("p = %p\n", p);

    return EXIT_SUCCESS;
}
