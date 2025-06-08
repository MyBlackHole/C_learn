#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define NUM 4096

// xmake run sys_mman_learn shm_open
//
// ls /dev/shm
// my_shared_memory
//
// cat /dev/shm/my_shared_memory
// hello, world!
int demo_shm_open_main()
{
	const char *name = "/my_shared_memory";
	const char *buffer = "hello, world!\n";
	mode_t mode = DEFFILEMODE;
	int my_fd;
	size_t ret;

	// 创建共享内存对象
	my_fd = shm_open(name, O_CREAT | O_RDWR, mode);
	if (my_fd == -1) {
		perror("shm_open");
		exit(EXIT_FAILURE);
	}

	// 设置共享内存的大小
	off_t size = NUM; // 4KB
	if (ftruncate(my_fd, size) == -1) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	ret = write(my_fd, buffer, strlen(buffer) + 1);
	if (ret < 0 || ret != (strlen(buffer) + 1)) {
		perror("write failed");
		exit(EXIT_FAILURE);
	}
	close(my_fd);
	return EXIT_SUCCESS;
}
