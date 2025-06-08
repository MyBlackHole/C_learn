#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t ngx_murmur_hash2(char *data, size_t len)
{
	uint32_t h_1, k_1;

	h_1 = 0 ^ len;

	while (len >= 4) {
		k_1 = data[0];
		k_1 |= data[1] << 8;
		k_1 |= data[2] << 16;
		k_1 |= data[3] << 24;

		k_1 *= 0x5bd1e995;
		k_1 ^= k_1 >> 24;
		k_1 *= 0x5bd1e995;

		h_1 *= 0x5bd1e995;
		h_1 ^= k_1;

		data += 4;
		len -= 4;
	}

	switch (len) {
	case 3:
		h_1 ^= data[2] << 16;
	case 2:
		h_1 ^= data[1] << 8;
	case 1:
		h_1 ^= data[0];
		h_1 *= 0x5bd1e995;
	}

	h_1 ^= h_1 >> 13;
	h_1 *= 0x5bd1e995;
	h_1 ^= h_1 >> 15;

	return h_1;
}
