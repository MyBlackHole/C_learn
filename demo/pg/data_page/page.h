#ifndef PAGE_H
#define PAGE_H

#include <stdbool.h>
#include <stdint.h>

#define FLEXIBLE_ARRAY_MEMBER

typedef uint16_t LocationIndex;
typedef uint64_t TransactionId;

typedef struct {
	uint32_t xlogid; /* high bits */
	uint32_t xrecoff; /* low bits */
} PageXLogRecPtr;

typedef struct ItemIdData {
	unsigned lp_off : 15, /* offset to tuple (from start of page) */
		lp_flags : 2, /* state of line pointer, see below */
		lp_len : 15; /* byte length of tuple */
} ItemIdData;

typedef struct PageHeaderData {
	/* XXX LSN is member of *any* block, not only page-organized ones */
	PageXLogRecPtr pd_lsn; /* LSN: next byte after last byte of xlog
								 * record for last change to this page */
	uint16_t pd_checksum; /* checksum */
	uint16_t pd_flags; /* flag bits, see below */
	LocationIndex pd_lower; /* offset to start of free space */
	LocationIndex pd_upper; /* offset to end of free space */
	LocationIndex pd_special; /* offset to start of special space */
	uint16_t pd_pagesize_version;
	TransactionId pd_prune_xid; /* oldest prunable XID, or zero if none */
	ItemIdData pd_linp[FLEXIBLE_ARRAY_MEMBER]; /* line pointer array */
} PageHeaderData;

static inline bool PageIsNew(const char *page)
{
	return ((PageHeaderData *)page)->pd_upper == 0;
}

#endif /* PAGE_H */
