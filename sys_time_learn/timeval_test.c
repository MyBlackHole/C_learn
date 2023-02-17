/**
 * @file 1.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/18 21:41:33
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>

void setTimer(int seconds, int mseconds)
{
    struct timeval temp;
    temp.tv_sec = seconds;
    temp.tv_usec = mseconds * 1000;
    select(0, NULL, NULL, NULL, &temp);
    printf("timer\n");
}

int main()
{
    int i;
    for (i = 0; i < 100; i++)
    {
        setTimer(1, 0);
    }
    return 0;
}
