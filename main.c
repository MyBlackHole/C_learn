//
// Created by BlackHole on 2020/7/16.
//
#include "stdio.h"
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

typedef unsigned long UINTPTR;
typedef unsigned int UINT32;

int add(int a, int b) {
    return a + b;
}

UINTPTR LOS_Align(UINTPTR addr, UINT32 boundary) {
    if ((addr + boundary - 1) > addr) {
        return (addr + boundary - 1) & ~((UINTPTR) (boundary - 1));
    } else {
        return addr & ~((UINTPTR) (boundary - 1));
    }
}

int function(void) {
    static int i, state = 0;
    switch (state) {
        case 0: goto LABEL0;
        case 1: goto LABEL1;
    }
    LABEL0: /* start of function */
    for (i = 0; i < 10; i++) {
        state = 1; /* so we will come back to LABEL1 */
        return i;
        LABEL1:; /* resume control straight after the return */
    }
}

static uint32_t dict_hash_function_seed = 5381;

unsigned int dictGenHashFunction(const void *key, int len) {
    /* 'm' and 'r' are mixing constants generated offline.
     They're not really 'magic', they just happen to work well.  */
    uint32_t seed = dict_hash_function_seed;
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    /* Initialize the hash to a 'random' value */
    uint32_t h = seed ^ len;

    /* Mix 4 bytes at a time into the hash */
    const unsigned char *data = (const unsigned char *)key;

    while(len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    /* Handle the last few bytes of the input array  */
    switch(len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0]; h *= m;
    };

    /* Do a few final mixes of the hash to ensure the last few
     * bytes are well-incorporated. */
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return (unsigned int)h;
}

// static unsigned int dictGenHashFunction(const unsigned char *buf, int len) {
//     unsigned int hash = 5381;

//     while (len--)
//         hash = ((hash << 5) + hash) + (*buf++); /* hash * 33 + c */
//     return hash;
// }


char *strlwr(char *str)
{
    unsigned char *p = (unsigned char *)str;
    while (*p) {
        *p = (unsigned char)tolower((int)*p);
        p++;
    }

    return str;
}



int main(int argc, char *argv[]) {

    char c = 'A';

    // char *s = (char *)malloc(3 * sizeof(char));
    char s[3];
    s[0] = 'O';
    s[1] = 'K';
    s[2] = '\0';

    printf("%c\n", (char)tolower((int)c));

    printf("%s\n", strlwr(s));

    int i = 1 << 1;
    int j = ~0;

    printf("%d\n", 1 << 1);
    printf("%u\n", j ^ i);

    printf("%d\n", dictGenHashFunction("okk", 3));

    // printf("%d", function());
    // printf("%d", function());
    // printf("%d", function());
    // printf("%d", function());

    // int t[2] = {0};
    // printf("%d-%d", t[0], t[1]);
    // if ( 1 ){
    //     printf("%d", 0);
    // }
//    printf("%d", argc);
//    for (int i = 0; i < argc; i++) {
//        printf("%s", argv[i]);
//    }
//    int input = 8;
//    int c;
//    c = LOS_Align(7, 3);
//    printf("%d", c);
//    return 0;
}
