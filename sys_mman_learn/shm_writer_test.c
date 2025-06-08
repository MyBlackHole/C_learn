#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MMAP_DATA_SIZE 1024

#define USE_MMAP 1

int demo_shm_writer_main(int argc, char *argv[])
{
	char *data;
	// 创建打开共享内存
	int shm_fd = shm_open("shm-file0001", O_CREAT | O_RDWR, ACCESSPERMS);

	if (shm_fd < 0) {
		printf("shm_open failed!\n");
		return -1;
	}

	// 修改共享区大小
	ftruncate(shm_fd, MMAP_DATA_SIZE);
	if (USE_MMAP) {
		// 映射目标的存储区
		data = (char *)mmap(NULL, MMAP_DATA_SIZE,
				    PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd,
				    0);
		if (!data) {
			printf("mmap failed\n");
			close(shm_fd);
		}

		// 数据写入共享区
		sprintf(data, "This is a share memory! %d\n", shm_fd);

		munmap(data, MMAP_DATA_SIZE);
	} else {
		char buf[MMAP_DATA_SIZE];
		int len = sprintf(
			buf, "This is a share memory by write! ! %d\n", shm_fd);
		if (write(shm_fd, buf, len) <= 0) {
			printf("write file %d failed!%d\n", len, errno);
		}
	}

	close(shm_fd);
	getchar();

	// 删除共享
	shm_unlink("shm-file0001");

	return 0;
}
