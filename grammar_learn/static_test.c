#include <stdio.h>
#include <stdlib.h>

void test()
{
    static int j;
    printf("%d\n", j++);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 5; i++)
    {
        test();
    }
    return 0;
}
