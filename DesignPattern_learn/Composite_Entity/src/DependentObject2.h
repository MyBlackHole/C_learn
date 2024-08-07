#ifndef DEPENDENT_OBJECT2_H_
#define DEPENDENT_OBJECT2_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DependentObject2 DependentObject2;

DependentObject2 *dependent_object2_create(void);

void dependent_object2_destroy(DependentObject2 **dependent_object2);

void dependent_object2_set_data(DependentObject2 *dependent_object2,
				const char *data);

const char *dependent_object2_get_data(DependentObject2 *dependent_object2);

#ifdef __cplusplus
}
#endif
#endif // DEPENDENT_OBJECT2_H_
