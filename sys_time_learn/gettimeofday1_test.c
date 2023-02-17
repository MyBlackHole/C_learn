#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(void)
{
    int i;
    struct timeval tv;

    for (i = 0; i < 4; i++)
    {
        gettimeofday(&tv, NULL);
        printf("%ld\t%ld\n", tv.tv_usec, tv.tv_sec);
        sleep(1);
    }

    return 0;
}
