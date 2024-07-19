#include <stdio.h>
#include <stdlib.h>

#include "ShapeStruct.h"

typedef struct {
	int radius;
	int x;
	int y;
	struct DrawAPI *draw_api;
} priv_t;

static void shape_init(struct Shape *shape, int radius, int x, int y,
		       struct DrawAPI *draw_api)
{
	shape->priv = calloc(1, sizeof(priv_t));
	priv_t *priv = shape->priv;
	priv->radius = radius;
	priv->x = x;
	priv->y = y;
	priv->draw_api = draw_api;
}

static void shape_draw(struct Shape *shape)
{
	priv_t *priv = shape->priv;
	if (NULL == priv) {
		return;
	}

	if (priv->draw_api && priv->draw_api->draw_circle) {
		priv->draw_api->draw_circle(priv->draw_api, priv->radius,
					    priv->x, priv->y);
	}
}

static void shape_destroy(struct Shape *shape)
{
	if (NULL != shape->priv) {
		free(shape->priv);
		shape->priv = NULL;
	}
}

struct Shape *circle_create(int radius, int x, int y, struct DrawAPI *draw_api)
{
	struct Shape *shape = (struct Shape *)calloc(1, sizeof(struct Shape));
	if (NULL == shape) {
		return NULL;
	}

	shape_init(shape, radius, x, y, draw_api);
	shape->draw = shape_draw;
	shape->destroy = shape_destroy;
	return shape;
}
