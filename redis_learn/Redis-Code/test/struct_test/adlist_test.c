//
// Created by Black Hole on 2020/12/5.
//

#include "adlist.h"
#include <stdio.h>

int
main() {
    struct list *l = listCreate();
    listAddNodeHead(l, (int *) 13);
    printf("%d\n", (int) l->head->value);
    printf("%d\n", (int) sizeof(size_t));
    listRelease(l);
    return 0;
}

