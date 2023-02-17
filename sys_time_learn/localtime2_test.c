#include <stdio.h>
#include <time.h>

#define TIMESTRSIZE 1024

int main(int argc, char *argv[])
{
    time_t stamp;
    struct tm *tm;
    char timestr[TIMESTRSIZE];

    stamp = time(NULL);
    tm = localtime(&stamp);
    strftime(timestr, TIMESTRSIZE, "NOW:%Y-%m-%d", tm);
    puts(timestr);

    tm->tm_mday += 100;
    // 处理溢出
    mktime(tm);
    strftime(timestr, TIMESTRSIZE, "100 days later:%Y-%m-%d", tm);
    puts(timestr);

    return 0;
}
