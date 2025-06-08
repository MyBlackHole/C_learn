#ifndef SHAPE_H_
#define SHAPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Shape Shape;

void shape_draw(Shape *shape);

void shape_destory(Shape **shape);

#ifdef __cplusplus
}
#endif
#endif // SHAPE_H_
