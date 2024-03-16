#include <stdio.h>
#include <stdint.h>

char              data_1[] = "hello";
static char       data_2[] = "world";
const static char data_3[] = "!!!";

int main(int argc, char *argv[])
{
    printf("%s %s%s\r\n", data_1, data_2, data_3);

    printf("0x%p 0x%p 0x%p\r\n", data_1, &data_2, &data_3);
    return 0;
}
