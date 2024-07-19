#include <stddef.h>
#include <stdlib.h>
#include "DrawAPI.h"

#include "DrawAPIStruct.h"

void draw_api_destroy(DrawAPI **draw_api)
{
	if (NULL == draw_api || NULL == *draw_api) {
		return;
	}

	if (NULL != (*draw_api)->destroy) {
		(*draw_api)->destroy(*draw_api);
	}
	free(*draw_api);
	*draw_api = NULL;
}
