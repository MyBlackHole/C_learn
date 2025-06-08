#include "zfs-tools.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int ret = 0;
	int fd = 0;
	char *zfs_stream_file = NULL;

	int ready = 0;
	int offset = 0;
	uint64_t payload_size = 0;
	const dmu_replay_record_t record = { 0 };
	const int header_size = sizeof(record);
	const dmu_replay_record_t *record_ptr = &record;
	uint32_t drr_type = 0;

	if (argc < 2) {
		printf("Usage: %s <zfs stream file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	zfs_stream_file = argv[1];

	fd = open(zfs_stream_file, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return EXIT_FAILURE;
	}

	while (true) {
		printf("[----------------------]\n");
		ready = pread(fd, (char *)record_ptr, header_size, offset);
		if (ready != header_size) {
			perror("read");
			ret = EXIT_FAILURE;
			goto return__;
		}

		offset += header_size;
		drr_type = record_ptr->drr_type;
		switch (drr_type) {
		case DRR_BEGIN: {
			printf("[DRR_BEGIN]\n");
			const struct drr_begin *begin =
				&record_ptr->drr_u.drr_begin;
			printf("toguid: %lu\n", begin->drr_toguid);
			printf("toname: %s\n", begin->drr_toname);
			break;
		}
		case DRR_OBJECT: {
			printf("[DRR_OBJECT]\n");
			const struct drr_object *obj =
				&record_ptr->drr_u.drr_object;
			payload_size = DRR_OBJECT_PAYLOAD_SIZE(obj);
			offset += payload_size;
			printf("drr_object: %lu\n", obj->drr_object);
			printf("type: %u\n", obj->drr_type);
			printf("payload_size: %lu\n", payload_size);
			break;
		}
		case DRR_FREEOBJECTS: {
			printf("[DRR_FREEOBJECTS]\n");
			const struct drr_freeobjects *fo =
				&record_ptr->drr_u.drr_freeobjects;
			printf("toguid: %lu\n", fo->drr_toguid);
			break;
		}
		case DRR_WRITE: {
			printf("[DRR_WRITE]\n");
			const struct drr_write *drrw =
				&record_ptr->drr_u.drr_write;
			payload_size = DRR_WRITE_PAYLOAD_SIZE(drrw);
			offset += payload_size;

			printf("object: %lu\n", drrw->drr_object);
			printf("offset: %lu\n", drrw->drr_offset);
			printf("payload_size: %lu\n", payload_size);
			printf("compressiontype: %u\n",
			       drrw->drr_compressiontype);
			break;
		}
		case DRR_WRITE_BYREF: {
			printf("[DRR_WRITE_BYREF]\n");
			const struct drr_write_byref *drrwb =
				&record_ptr->drr_u.drr_write_byref;
			printf("offset: %lu\n", drrwb->drr_offset);
			printf("object: %lu\n", drrwb->drr_object);
			break;
		}
		case DRR_WRITE_EMBEDDED: {
			printf("[DRR_WRITE_EMBEDDED]\n");
			const struct drr_write_embedded *drrwe =
				&record_ptr->drr_u.drr_write_embedded;
			printf("offset: %lu\n", drrwe->drr_offset);
			printf("object: %lu\n", drrwe->drr_object);

			break;
		}
		case DRR_FREE: {
			printf("[DRR_FREE]\n");
			const struct drr_free *drrf =
				&record_ptr->drr_u.drr_free;
			printf("object: %lu\n", drrf->drr_object);
			printf("offset: %lu\n", drrf->drr_offset);

			break;
		}
		case DRR_END: {
			printf("[DRR_END]\n");
			ret = 0;
			goto return__;
		}
		case DRR_SPILL: {
			printf("[DRR_SPILL]\n");
			const struct drr_spill *drrs =
				&record_ptr->drr_u.drr_spill;
			payload_size = DRR_SPILL_PAYLOAD_SIZE(drrs);
			offset += payload_size;
			printf("object: %lu\n", drrs->drr_object);
			printf("length: %lu\n", drrs->drr_length);
			printf("payload_size: %lu\n", payload_size);
			break;
		}
		case DRR_OBJECT_RANGE: {
			printf("[DRR_OBJECT_RANGE]\n");
			const struct drr_object_range *drror =
				&record_ptr->drr_u.drr_object_range;
			printf("toguid: %lu\n", drror->drr_toguid);
			break;
		}
		default: {
			printf("Unknown DRR type: %u\n", drr_type);
			printf("offset: %u\n", offset);
			ret = EXIT_FAILURE;
			goto return__;
		}
		}
	}
return__:
	close(fd);
	return ret;
}
