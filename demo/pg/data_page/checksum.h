#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <string.h>
#include <stdint.h>

#include "page.h"

#define N_SUMS 32
#define FNV_PRIME 16777619

static const uint32_t checksumBaseOffsets[N_SUMS] = {
	0x5B1F36E9, 0xB8525960, 0x02AB50AA, 0x1DE66D2A, 0x79FF467A, 0x9BB9F8A3,
	0x217E7CD2, 0x83E13D2C, 0xF8D4474F, 0xE39EB970, 0x42C6AE16, 0x993216FA,
	0x7B093B5D, 0x98DAFF3C, 0xF718902A, 0x0B1C9CDB, 0xE58F764B, 0x187636BC,
	0x5D7B3BB1, 0xE73DE7DE, 0x92BEC979, 0xCCA6C0B2, 0x304A0979, 0x85AA43D4,
	0x783125BB, 0x6CA8EAA2, 0xE407EAC6, 0x4B5CFC3E, 0x9FBF8C76, 0x15CA20BE,
	0xF2CA9FD3, 0x959BD756
};

#define CHECKSUM_COMP(checksum, value)                          \
	do {                                                    \
		uint32_t __tmp = (checksum) ^ (value);          \
		(checksum) = __tmp * FNV_PRIME ^ (__tmp >> 17); \
	} while (0)

static uint32_t pg_checksum_block(const char *page, uint32_t page_size)
{
	uint32_t sums[N_SUMS];
	uint32_t result = 0;
	uint32_t i, j;
	uint32_t data[page_size / (sizeof(uint32_t) * N_SUMS)][N_SUMS];

	memcpy(sums, checksumBaseOffsets, sizeof(checksumBaseOffsets));

	for (i = 0; i < (uint32_t)(page_size / (sizeof(uint32_t) * N_SUMS));
	     i++)
		for (j = 0; j < N_SUMS; j++)
			CHECKSUM_COMP(sums[j], data[i][j]);

	for (i = 0; i < 2; i++)
		for (j = 0; j < N_SUMS; j++)
			CHECKSUM_COMP(sums[j], 0);

	for (i = 0; i < N_SUMS; i++)
		result ^= sums[i];

	return result;
}

uint16_t pg_checksum_page(const char *page, uint32_t page_size, uint32_t blkno)
{
	uint32_t checksum;
	PageHeaderData *cpage = (PageHeaderData *)page;

	cpage->pd_checksum = 0;
	checksum = pg_checksum_block(page, page_size);

	checksum ^= blkno;

	return (uint16_t)((checksum % 65535) + 1);
}
#endif /* CHECKSUM_H */
