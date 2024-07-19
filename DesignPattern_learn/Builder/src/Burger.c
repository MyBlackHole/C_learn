#include "BurgerStruct.h"
#include "Packing.h"

struct Packing *burger_packing_default(struct Item *item)
{
	return wrapper_create();
}
