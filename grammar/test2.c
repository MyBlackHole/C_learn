#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct FileMetaHead {
	// uint64_t hash;
	uint64_t timestamp;
	uint64_t fileSize;
	uint64_t fileSizeExt;
	int64_t cache_id;
	int64_t bitmap_id; //-1 is len 0 file , -2 new file or dir, -3 is delete, -4 is symlink
	uint32_t st_mode;
	uint32_t st_uid;
	uint32_t st_gid;
	int64_t st_atim;
	int64_t st_mtim;
	char filePath[512];
};

int demo_test2_main(int argc, char *argv[])
{
	struct FileMetaHead *meta =
		(struct FileMetaHead *)malloc(sizeof(struct FileMetaHead));
	printf("FileMetaHead size: %ld", sizeof(struct FileMetaHead));
	printf("FileMetaHead size: %ld", sizeof(*meta));
	return EXIT_SUCCESS;
}
