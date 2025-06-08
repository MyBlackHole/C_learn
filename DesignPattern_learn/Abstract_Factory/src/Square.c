#include <stdio.h>
#include <stdlib.h>

#include "ShapeStruct.h"

static void shape_draw(struct Shape *shape)
{
	printf("Inside Square::draw() method.\n");
}

struct Shape *square_create(void)
{
	struct Shape *shape = (struct Shape *)calloc(1, sizeof(struct Shape));
	if (NULL == shape) {
		return NULL;
	}

	shape->draw = shape_draw;
	return shape;
}
