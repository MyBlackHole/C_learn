#include <assert.h>
#include <stdlib.h>

#include "ShapeStruct.h"

void shape_draw(struct Shape *shape)
{
	assert(NULL != shape);
	if (NULL != shape) {
		shape->draw(shape);
	}
}

void shape_destory(struct Shape **shape)
{
	if (NULL == shape || NULL == *shape) {
		return;
	}

	struct Shape *self = *shape;
	if (NULL != self->destroy) {
		self->destroy(self);
	}

	free(*shape);
	*shape = NULL;
}
