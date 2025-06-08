#include <stdio.h>
#include <stdlib.h>

#include "PackingStruct.h"

static const char *pack(struct Packing *packing)
{
	return "Bottle";
}

struct Packing *bottle_create(void)
{
	struct Packing *packing =
		(struct Packing *)calloc(1, sizeof(struct Packing));
	if (NULL == packing) {
		return NULL;
	}

	packing->pack = pack;
	return packing;
}
