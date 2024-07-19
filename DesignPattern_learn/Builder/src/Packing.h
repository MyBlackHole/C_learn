#ifndef PACKING_H_
#define PACKING_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Packing Packing;

Packing *wrapper_create(void);
Packing *bottle_create(void);
const char *packing_pack(Packing *packing);
void packing_destroy(Packing **packing);

#ifdef __cplusplus
}
#endif
#endif // PACKING_H_
