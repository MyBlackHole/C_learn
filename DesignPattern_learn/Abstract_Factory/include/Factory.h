#ifndef FACTORY_H_
#define FACTORY_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Factory Factory;

struct Shape *factory_get_shape(Factory *shape_factory, const char *shape_type);

struct Color *factory_get_color(Factory *color_factory, const char *color_type);

void factory_destory(Factory **factory);

#ifdef __cplusplus
}
#endif
#endif // FACTORY_H_
