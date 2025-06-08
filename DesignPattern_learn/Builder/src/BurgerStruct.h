#ifndef BURGER_STRUCT_H_
#define BURGER_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ItemStruct.h"

struct Burger {
	struct Item item;
	void *parent;
	void *priv;

	void (*destroy)(struct Burger *);
};

struct Packing *burger_packing_default(struct Item *);

#ifdef __cplusplus
}
#endif
#endif // BURGER_STRUCT_H_
