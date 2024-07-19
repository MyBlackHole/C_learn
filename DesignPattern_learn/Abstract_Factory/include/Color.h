#ifndef COLOR_H_
#define COLOR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Color Color;

void color_fill(Color *color);

void color_destory(Color **color);

#ifdef __cplusplus
}
#endif
#endif // COLOR_H_
