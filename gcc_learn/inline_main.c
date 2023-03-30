#include <stdio.h>

inline int test1();

int main()
{
    test1();
    return 0;
}

int test1()
{
    printf("%s\n", __FUNCTION__);
    return 0;
}
