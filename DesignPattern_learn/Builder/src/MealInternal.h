#ifndef MEAL_INTERNAL_H_
#define MEAL_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Item.h"
#include "Meal.h"

Meal *meal_create(void);
void meal_add_items(Meal *meal, Item *item);

#ifdef __cplusplus
}
#endif
#endif // MEAL_INTERNAL_H_
