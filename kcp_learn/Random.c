#include "Random.h"
#include <stdlib.h>
#include <tbox/container/element.h>
#include <tbox/container/iterator.h>
#include <tbox/container/vector.h>

Random *createRandom(int size)
{
	struct Random *random = NULL;
	random = malloc(sizeof(*random));
	random->size = 0;
	random->seeds = tb_vector_init(size, tb_element_long());
	return random;
}

void destroyRandom(Random *random)
{
	if (!random) {
		return;
	}
	if (!random->seeds) {
		// free(random->seeds);
		// tb_vector_clear(random->seeds);
		tb_vector_exit(random->seeds);
	}
	free(random);
}

int getRandom(Random *random)
{
	int x, i;
	if (tb_vector_size(random->seeds) == 0)
		return 0;
	if (random->size == 0) {
		for (i = 0; i < tb_vector_size(random->seeds); i++) {
			tb_iterator_copy(random->seeds, i,
					 (tb_pointer_t)(tb_long_t *)&i);
		}
		random->size = (int)tb_vector_size(random->seeds);
	}
	i = rand() % random->size;
	x = *(int *)tb_iterator_item(random->seeds, i);
	tb_iterator_copy(random->seeds, i,
			 tb_iterator_item(random->seeds, --random->size));
	return x;
}
