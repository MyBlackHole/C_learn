#include "Array_gp.h"

#include <stdbool.h>
#include <string.h>

Array *arrayCreate()
{
	struct Array *array = NULL;
	array = malloc(sizeof(*array));
	if (NULL == array) {
		return NULL;
	}

	array->p = NULL;

	array->size = 0;
	array->typeSize = 0;
	array->len = 0;

	array->dup = NULL;
	array->free = NULL;
	array->match = NULL;

	return array;
}

void arrayInit(Array *array, int size, int typeSize)
{
	if (NULL == array || typeSize <= 0 || size < 0) {
		return;
	}

	void *data = calloc(1, size * typeSize);
	if (NULL == data) {
		return;
	}

	array->p = data;
	array->len = 0;
	array->size = size;
	array->typeSize = typeSize;
}

int arrayInsert(Array *array, size_t pos, void *const value)
{
	if (NULL == array) {
		return -1;
	}

	if (array->len >= array->size) {
		return -2;
	}

	if (pos > array->size || pos <= 0) {
		return -3;
	}

	char *begin_p = array->p;
	for (size_t i = array->len; i > pos - 1; --i) {
		void *new_p = begin_p + i * array->typeSize;
		void *old_p = begin_p + (i - 1) * array->typeSize;
		if (NULL != array->dup) {
			array->dup(new_p, old_p);
		} else {
			memcpy(new_p, old_p, array->typeSize);
		}
	}

	void *copy_p = (void *)(begin_p + ((pos - 1) * array->typeSize));
	if (NULL != array->dup) {
		array->dup(copy_p, value);
	} else {
		memcpy(copy_p, value, array->typeSize);
	}
	++array->len;
	return 0;
}

size_t arraySearchValue(Array *array, void *const value)
{
	if (NULL == array) {
		return -1;
	}

	char *begin_p = array->p;
	size_t index = 0;
	for (; index < array->len; ++index) {
		int cmp_n = 0;
		if (NULL != array->match) {
			cmp_n = array->match(begin_p + index * array->typeSize,
					     value);
		} else {
			cmp_n = memcmp(begin_p + index * array->typeSize, value,
				       array->typeSize);
		}

		if (cmp_n == 0) {
			break;
		}
	}

	return index;
}

void *arrayIndex(Array *array, size_t index)
{
	if (NULL == array) {
		return NULL;
	}

	if (index > array->len || index <= 0) {
		return NULL;
	}

	char *begin_p = array->p;
	return begin_p + array->typeSize * (index - 1);
}

int arrayModify(Array *array, size_t pos, void *const value)
{
	if (NULL == array) {
		return -1;
	}
	if (pos > array->len || pos <= 0) {
		return -2;
	}

	char *begin_p = array->p;
	void *old_p = begin_p + (pos - 1) * array->typeSize;
	if (NULL != array->dup) {
		array->dup(old_p, value);
	} else {
		memcpy(old_p, value, array->typeSize);
	}

	return 0;
}

size_t arrayLen(Array *array)
{
	if (NULL == array) {
		return 0;
	}

	return array->len;
}

size_t arraySize(Array *array)
{
	if (NULL == array) {
		return 0;
	}

	return array->size;
}

void arrayEmpty(Array *array)
{
	if (NULL == array) {
		return;
	}

	free(array->p);
	array->p = NULL;
	free(array);
	array = NULL;
}

void arrayDelValue(Array *array, void *value)
{
	if (NULL == array) {
		return;
	}

	char *begin_p = array->p;
	bool copy_p = false;
	for (size_t i = 0; i < array->len; ++i) {
		if (!copy_p) {
			int cmp_n = 0;
			if (NULL != array->match) {
				cmp_n = array->match(
					begin_p + i * array->typeSize, value);
			} else {
				cmp_n = memcmp(begin_p + i * array->typeSize,
					       value, array->typeSize);
			}

			if (0 == cmp_n) {
				copy_p = true;
				continue;
			}
		} else {
			void *old_p = begin_p + (i + 1) * array->typeSize;
			void *new_p = begin_p + i * array->typeSize;
			if (NULL != array->dup) {
				array->dup(new_p, old_p);
			} else {
				memcpy(new_p, old_p, array->typeSize);
			}
		}
	}

	if (copy_p) {
		--array->len;
	}
}

void arrayDelIndex(Array *array, size_t pos)
{
	if (NULL == array) {
		return;
	}

	if (pos > array->len || pos <= 0) {
		return;
	}

	char *begin_p = array->p;
	for (size_t i = pos - 1; i < array->len - 1; ++i) {
		void *old_p = begin_p + (i + 1) * array->typeSize;
		void *new_p = begin_p + i * array->typeSize;
		if (NULL != array->dup) {
			array->dup(new_p, old_p);
		} else {
			memcpy(new_p, old_p, array->typeSize);
		}
	}

	--array->len;
}
