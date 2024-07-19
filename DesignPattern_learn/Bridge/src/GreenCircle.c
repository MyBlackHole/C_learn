#include <stdio.h>
#include <stdlib.h>

#include "DrawAPIStruct.h"

static void draw_circle(struct DrawAPI *draw_api, int radius, int x, int y)
{
	printf("Drawing Circle[ color: green, radius: %d, x: %d, y: %d\n",
	       radius, x, y);
}

struct DrawAPI *green_circle_create(void)
{
	struct DrawAPI *api =
		(struct DrawAPI *)calloc(1, sizeof(struct DrawAPI));
	if (NULL == api) {
		return NULL;
	}

	api->draw_circle = draw_circle;
	return api;
}
