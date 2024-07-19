#ifndef SHAPE_STRUCT_H_
#define SHAPE_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DrawAPIStruct.h"

struct Shape {
	void *priv;

	void (*draw)(struct Shape *shape);
	void (*destroy)(struct Shape *shape);
};

#ifdef __cplusplus
}
#endif
#endif // SHAPE_STRUCT_H_
