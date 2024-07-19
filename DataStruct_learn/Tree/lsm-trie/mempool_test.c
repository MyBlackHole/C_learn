#include "mempool.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	size_t cap = 10;
	struct Mempool *m = NULL;
	m = mempool_new(cap);
	return 0;
}
