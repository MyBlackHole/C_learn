#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct ReplicationSlotPersistentData {
	char synced;
} ReplicationSlotPersistentData;

typedef struct ReplicationSlotOnDisk {
	/* first part of this struct needs to be version independent */

	/* data not covered by checksum */
	uint32_t magic;
	uint32_t checksum;

	/* data covered by checksum */
	uint32_t version;
	uint32_t length;

	/*
	 * The actual data in the slot that follows can differ based on the above
	 * 'version'.
	 */

	ReplicationSlotPersistentData slotdata;
} ReplicationSlotOnDisk;

#define ReplicationSlotOnDiskConstantSize \
	offsetof(ReplicationSlotOnDisk, slotdata)

int main(int argc, char *argv[])
{
	printf("%ld\n", ReplicationSlotOnDiskConstantSize);
	return EXIT_SUCCESS;
}

// output:
// 
// xmake run replication_slot
// 16
