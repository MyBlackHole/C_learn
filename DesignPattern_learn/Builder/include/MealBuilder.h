#ifndef MEAL_BUILDER_H_
#define MEAL_BUILDER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Meal.h"

Meal *meal_builder_prepare_veg_meal(void);
Meal *meal_builder_prepare_non_veg_meal(void);

#ifdef __cplusplus
}
#endif
#endif // MEAL_BUILDER_H_
