#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM 10

typedef struct {
	char name[4];
	int age;
} people;

// map a normal file as shared mem:
int demo_mmap_main(int argc, char **argv)
{
	int myfd;
	int index;
	people *p_map;
	size_t ret;
	// 以读写方式打开， 没有自动创建
	myfd = open(argv[1], O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	if (myfd < 0) {
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}

	// 文件大小不能为 0
	// 否则读取异常
	ret = write(myfd, "\n", 1);
	if (ret < 0) {
		printf("write %s \n", strerror((int)ret));
		exit(EXIT_FAILURE);
	}

	p_map = mmap(NULL, sizeof(people) * NUM, PROT_READ | PROT_WRITE,
		     MAP_SHARED, myfd, 0);
	if (p_map == MAP_FAILED) {
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}

	char str[2];
	for (index = 0; index < NUM; index++) {
		(*(p_map + index)).age = index;
		sprintf(str, "%d", index);
		memccpy(&(*(p_map + index)).name, &str, sizeof(char), 2);
		printf("name: %s age %d;\n", (*(p_map + index)).name,
		       (*(p_map + index)).age);
	}

	// 解除映射时会把内存数据写回文件(后台达到条件也会写)，
	// 但是不会超出文件大小
	munmap(p_map, sizeof(people) * NUM);
	exit(EXIT_SUCCESS);
}
