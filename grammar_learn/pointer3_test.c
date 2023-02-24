#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char c = 'c';
    char c1 = 'c';
    const char *const p_c = &c;
    // // const p_c: 不允许修改 p_c 这片内存
    // p_c = &c;
    // // const char :不允许修改 *p_c
    // *p_c = 'b';
    printf("&c = [%p], p_c = [%p], *p_c = [%c]\n", &c, p_c, *p_c);
    char *const p_c1 = &c;
    // // const p_c1: 不允许修改 p_c1 这片内存
    // p_c1 = &c;
    *p_c1 = 'b';
    printf("&c = [%p], p_c1 = [%p], *p_c1 = [%c]\n", &c, p_c, *p_c1);
    const char *p_c2 = &c;
    p_c2 = &c1;
    // // const char :不允许修改 *p_c2
    // *p_c2 = 'b';
    printf("&c = [%p], p_c2 = [%p], *p_c2 = [%c]\n", &c, p_c2, *p_c2);

    char *const *const pp_c1 = &p_c1;
    // // const :不允许修改 pp_c1
    // pp_c1 = &pp_c1;
    // // const :不允许修改 *pp_c2
    // *pp_c1 = p_c1;
    **pp_c1 = '1';
    printf("&c = [%p], pp_c1 = [%p], *pp_c1 = [%p], **pp_c1 = [%c]\n", &c,
           pp_c1, *pp_c1, **pp_c1);

    const char **pp_c2 = &p_c2;
    *pp_c2 = p_c2;
    // // const char :不允许修改 **pp_c2
    // **pp_c2 = p_c2;
    printf("&c = [%p], pp_c2 = [%p], *pp_c2 = [%p], **pp_c2 = [%c]\n", &c,
           pp_c2, *pp_c2, **pp_c2);
    exit(0);
}
