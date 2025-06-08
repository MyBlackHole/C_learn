#ifndef DEPENDENT_OBJECT1_H_
#define DEPENDENT_OBJECT1_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DependentObject1 DependentObject1;

DependentObject1 *dependent_object1_create(void);

void dependent_object1_destroy(DependentObject1 **dependent_object1);

void dependent_object1_set_data(DependentObject1 *dependent_object1,
				const char *data);

const char *dependent_object1_get_data(DependentObject1 *dependent_object1);

#ifdef __cplusplus
}
#endif
#endif // DEPENDENT_OBJECT1_H_
