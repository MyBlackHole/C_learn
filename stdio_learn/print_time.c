#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

enum
{
    SECS_TO_SLEEP = 0,
    NSEC_TO_SLEEP = 10000000,
};

int main(int argc, char *argv[])
{
    struct tm tp;
    time_t t;
    char data_time[60];
    int rv;
    struct timespec remaining, request = {SECS_TO_SLEEP, NSEC_TO_SLEEP};

    while (1)
    {
        t = time(NULL);

        rv = nanosleep(&request, &remaining);
        // rv = nanosleep(&request, NULL);
        if (rv != 0)
        {
            printf("error: sleep: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }

        strftime(data_time, sizeof(data_time), "%Y-%m-%d %H:%M:%S",
                 gmtime_r(&t, &tp));
        printf("******************************************************** ");
        printf("增加中文测试 %s\n", data_time);
        // // 刷新系统缓冲区
        // sync();
    }

    return EXIT_SUCCESS;
}
