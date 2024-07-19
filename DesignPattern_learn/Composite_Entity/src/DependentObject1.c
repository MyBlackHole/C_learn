#include "DependentObject1.h"

#include "ctools.h"

struct DependentObject1 {
	const char *data;
};

DependentObject1 *dependent_object1_create(void)
{
	DependentObject1 *dependent_object1 =
		(DependentObject1 *)calloc(1, sizeof(DependentObject1));
	return dependent_object1;
}

void dependent_object1_destroy(DependentObject1 **dependent_object1)
{
	if (NULL == dependent_object1 || NULL == *dependent_object1)
		return;
	freep((void **)&(*dependent_object1)->data);
	freep((void **)dependent_object1);
}

void dependent_object1_set_data(DependentObject1 *dependent_object1,
				const char *data)
{
	if (NULL == dependent_object1)
		return;
	freep((void **)&dependent_object1->data);
	dependent_object1->data = cstrdup(data);
}

const char *dependent_object1_get_data(DependentObject1 *dependent_object1)
{
	if (NULL == dependent_object1)
		return NULL;
	return dependent_object1->data;
}
