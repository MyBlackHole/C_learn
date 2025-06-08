#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "ItemStruct.h"

const char *item_name(struct Item *item)
{
	if (NULL == item || NULL == item->name) {
		return NULL;
	}
	return item->name(item);
}

struct Packing *item_packing(struct Item *item)
{
	if (NULL == item || NULL == item->name) {
		return NULL;
	}
	return item->packing(item);
}

float item_price(struct Item *item)
{
	if (NULL == item || NULL == item->price) {
		return 0.0f;
	}
	return item->price(item);
}

void item_destroy(struct Item *item)
{
	if (NULL == item) {
		return;
	}
	if (NULL != item->child_destory) {
		item->child_destory(item->child);
	}
	if (NULL != item->destroy) {
		item->destroy(item);
	}
	memset(item, 0, sizeof(*item));
	free(item);
}
