#include "Packing.h"
#include "mem.h"

#include <stdlib.h>

#include "PackingStruct.h"

const char *packing_pack(Packing *packing)
{
	if (NULL == packing || NULL == packing->pack) {
		return NULL;
	}
	return packing->pack(packing);
}

void packing_destroy(Packing **packing)
{
	if (NULL == packing || NULL == *packing) {
		return;
	}

	Packing *self = *packing;
	if (NULL != self->destroy) {
		self->destroy(self);
	}
	freep((void **)packing);
}
