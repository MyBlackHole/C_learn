#ifndef MEAL_H_
#define MEAL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Meal Meal;

float meal_get_cost(Meal *meal);
void meal_show_items(Meal *meal);
void meal_destory(Meal **meal);

#ifdef __cplusplus
}
#endif
#endif // MEAL_H_
