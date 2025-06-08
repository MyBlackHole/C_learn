#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "PackingStruct.h"

static const char *pack(struct Packing *packing)
{
	return "Wrapper";
}

struct Packing *wrapper_create(void)
{
	struct Packing *packing =
		(struct Packing *)calloc(1, sizeof(struct Packing));
	if (NULL == packing) {
		return NULL;
	}

	packing->pack = pack;
	return packing;
}
