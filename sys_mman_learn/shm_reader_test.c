#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MMAP_DATA_SIZE 1024

int demo_shm_reader_main(int argc, char *argv[])
{
	char *data;
	int my_fd = shm_open("shm-file0001", O_RDWR, S_IRWXU);
	if (my_fd < 0) {
		printf("error open shm object\n");
		return MMAP_DATA_SIZE;
	}

	// mmap 映射减少用户态到内核台数据交换
	data = (char *)mmap(NULL, MMAP_DATA_SIZE, PROT_READ, MAP_SHARED, my_fd,
			    0);
	if (!data) {
		printf("mmap failed!\n");
		close(my_fd);
		return EXIT_FAILURE;
	}

	printf("%s\n", data);

	// 取消内存映射
	munmap(data, MMAP_DATA_SIZE);

	close(my_fd);
	getchar();

	return EXIT_SUCCESS;
}
