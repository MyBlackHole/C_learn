#ifndef FACTORY_STRUCT_H_
#define FACTORY_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct Factory {
	void *priv;

	struct Shape *(*get_shape)(struct Factory *factory,
				   const char *shape_type);
	struct Color *(*get_color)(struct Factory *factory,
				   const char *color_type);
	void (*destroy)(struct Factory *factory);
};

#ifdef __cplusplus
}
#endif
#endif // FACTORY_STRUCT_H_
