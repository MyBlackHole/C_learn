#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>
#include <stdlib.h>

void os_setup_limits(void)
{
    struct rlimit nofile;

    if (getrlimit(RLIMIT_NOFILE, &nofile) < 0)
    {
        fprintf(stderr, "unable to query NOFILE limit: %s", strerror(errno));
        return;
    }

    if (nofile.rlim_cur == nofile.rlim_max)
    {
        return;
    }

#ifdef CONFIG_DARWIN
    nofile.rlim_cur = OPEN_MAX < nofile.rlim_max ? OPEN_MAX : nofile.rlim_max;
#else
    nofile.rlim_cur = nofile.rlim_max;
    printf("Current NOFILE limit is %lu, setting to %lu\n", nofile.rlim_cur, nofile.rlim_max);
#endif

    if (setrlimit(RLIMIT_NOFILE, &nofile) < 0)
    {
        fprintf(stderr, "unable to set NOFILE limit: %s", strerror(errno));
        return;
    }
}

int demo_setrlimit_main(void)
{
    os_setup_limits();
    return EXIT_SUCCESS;
}
