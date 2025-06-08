#ifndef SHAPE_H_
#define SHAPE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DrawAPI.h"

typedef struct Shape Shape;

Shape *circle_create(int radius, int x, int y, struct DrawAPI *draw_api);
void shape_destory(Shape **shape);
void shape_draw(Shape *shape);

#ifdef __cplusplus
}
#endif
#endif // SHAPE_H_
