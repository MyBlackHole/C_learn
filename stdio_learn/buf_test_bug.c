#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("[%s:%d]before while().\n", __FUNCTION__, __LINE__);
    while (1)
    {
        ;
    }
    printf("[%s:%d]after while().\n", __FUNCTION__, __LINE__);
    return 0;
}
