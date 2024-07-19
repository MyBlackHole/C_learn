#include "ColdDrinkStruct.h"
#include "Packing.h"

struct Packing *cold_drink_packing_default(struct Item *item)
{
	return bottle_create();
}
