#include "murmurhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	uint32_t seed = 0;
	const char *key = "kinkajou";
	uint32_t hash =
		murmurhash(key, (uint32_t)strlen(key), seed); // 0xb6d99cf8
	printf("0x%x\n", hash);
	return 0;
}
