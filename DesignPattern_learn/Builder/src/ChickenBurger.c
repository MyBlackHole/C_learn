#include <stdlib.h>
#include "BurgerStruct.h"

static const char *item_name(struct Item *item)
{
	return "Chicken Burger";
}

static struct Packing *item_packing(struct Item *item)
{
	return burger_packing_default(item);
}

static float item_price(struct Item *item)
{
	return 50.5f;
}

struct Burger *chicken_burger_create(void)
{
	struct Burger *burger =
		(struct Burger *)calloc(1, sizeof(struct Burger));
	if (NULL == burger) {
		return NULL;
	}

	burger->item.name = item_name;
	burger->item.packing = item_packing;
	burger->item.price = item_price;
	burger->item.child = burger;
	burger->parent = &burger->item;
	return burger;
}
