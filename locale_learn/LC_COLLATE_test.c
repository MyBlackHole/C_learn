#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int main(void)
{
    int i;
    char str[10][4] = { "镕","堃","趙","錢","孫","李","周","吳","鄭","王" };
    qsort(str, 10, 4, strcoll);
    printf("按内码排序：");
    for (i = 0; i < 10; i++) {
        printf("%s", str[i]);
    }

    setlocale(LC_COLLATE, "zh_CN");  //在Windows下请写作 setlocale (LC_ALL,"zh-CN");
    qsort(str, 10, 4, strcoll);
    printf("\n按音序排序：");
    for (i = 0; i < 10; i++) {
        printf("%s", str[i]);
    }

    printf("\n");
    return 0;
}
