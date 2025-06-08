#ifndef COLOR_STRUCT_H_
#define COLOR_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct Color {
	void *priv;

	void (*fill)(struct Color *color);
	void (*destroy)(struct Color *color);
};

#ifdef __cplusplus
}
#endif
#endif // COLOR_STRUCT_H_
