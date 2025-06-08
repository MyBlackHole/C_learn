#ifndef PACKING_STRUCT_H_
#define PACKING_STRUCT_H_

#ifdef __cplusplus
extern "C" {
#endif

struct Packing {
	void *priv;

	const char *(*pack)(struct Packing *packing);
	void (*destroy)(struct Packing *packing);
};

#ifdef __cplusplus
}
#endif
#endif // PACKING_STRUCT_H_
