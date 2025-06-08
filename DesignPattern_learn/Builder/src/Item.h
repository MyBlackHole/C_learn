#ifndef ITEM_H_
#define ITEM_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Item Item;

const char *item_name(struct Item *item);

struct Packing *item_packing(struct Item *item);

float item_price(struct Item *item);

void item_destroy(struct Item *item);

#ifdef __cplusplus
}
#endif
#endif // ITEM_H_
