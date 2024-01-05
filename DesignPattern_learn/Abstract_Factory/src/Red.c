#include <stdio.h>
#include <stdlib.h>

#include "ColorStruct.h"

static void color_fill(struct Color *color)
{
    printf("Inside Red::fill() method.\n");
}

struct Color *red_create(void)
{
    struct Color *color = (struct Color *)calloc(1, sizeof(struct Color));
    if (NULL == color)
    {
        return NULL;
    }

    color->fill = color_fill;
    return color;
}
