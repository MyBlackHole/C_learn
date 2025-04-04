#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Line {
	uint32_t length;
	// 不占用空间, 柔性数组用法
	// uint8_t contents[];

	// 柔性数组用法
	uint8_t contents[1];
};

#pragma pack(1)
typedef struct file_meta_head {
	uint64_t timestamp;
	uint64_t fileSize;
	uint64_t fileSizeExt;
	int64_t cache_id;
	int64_t bitmap_id;
	uint32_t st_mode;
	uint32_t st_uid;
	uint32_t st_gid;
	int64_t st_atim;
	int64_t st_mtim;
	char filePath[512];
} file_meta_head_t;
#pragma pack()

int demo_struct1_main()
{
	struct Line line;
	int length = 100;

	printf("file_meta_head_t %ld\n", sizeof(file_meta_head_t));

	struct Line *line_ptr =
		(struct Line *)malloc(sizeof(struct Line) + length);
	memset(line_ptr, 0, sizeof(struct Line) + length);

	// 代表 contents 100 char
	line_ptr->length = 100;

	printf("%d\n", line_ptr->contents[96]);

	free(line_ptr);

	printf("%ld\n", sizeof(line));
	return EXIT_SUCCESS;
}
