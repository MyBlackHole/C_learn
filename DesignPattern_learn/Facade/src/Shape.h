/**
 * @file Shape.h
 * @author {Layne} ({shu_huanglei@163.com})
 * @brief
 * @version 0.1
 * @date 2020-08-01
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef SHAPE_H_
#define SHAPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Shape Shape;

void shape_destroy(Shape **shape);
void shape_draw(Shape *shape);

#ifdef __cplusplus
}
#endif
#endif // SHAPE_H_
