#include <stdio.h>
#include <string.h>

int main()
{
    char *s = "GoldenGlobalView";
    char *l = "lob";
    char *p;
    p = strstr(s, l);
    if (p)
    {
        printf("%s\n", p);
    }
    else
    {
        printf("NotFound!\n");
    }

    return 0;
}
