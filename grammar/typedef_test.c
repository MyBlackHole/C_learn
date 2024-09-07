#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

struct IncFileData {
	uint64_t offset;
	uint64_t size;
	char data[0];
};

typedef struct IncFileData IncFileData;

int demo_typedef_main(void)
{
	/*int fd_tmp = -1;*/
	// char file_path = "/home/black/pg_control.0.block";
	// char* buff = (char*)malloc(0xa00000 + sizeof(IncFileData));
	// read(int fd, void *buf, size_t nbytes)

	printf("%ld\n", sizeof(IncFileData));
	return EXIT_SUCCESS;
}
