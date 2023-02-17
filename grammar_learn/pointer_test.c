#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i = 0;
    int j = 1;
    int *p1;
    int *p2;
    int *p3;
    p1 = &i;
    p2 = p1;
    p3 = &j;
    *p3 = *p2;
    printf("i = %d\n", i);
    printf("p1 = %d\n", *p1);
    printf("p2 = %d\n", *p2);
    printf("p3 = %d\n", *p3);
    exit(0);
}
