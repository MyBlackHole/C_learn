#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

#define NUM 10
// 进制
#define NUM1 16
#define NUM2 50

int main(int argc, char *argv[])
{
	assert(argc == 4);
	// 将参数转化为数字
	long int pid = strtol(argv[1], NULL, NUM);
	unsigned long addr = strtoul(argv[2], NULL, NUM1);
	long int len = strtol(argv[3], NULL, NUM);
	// 得到 proc-1 进程的存储位置
	char *proc_mem = malloc(NUM2);
	sprintf(proc_mem, "/proc/%ld/mem", pid);
	printf("opening %s, address is %p\n", proc_mem, (void *)addr);
	// 打开存储位置
	int fd_proc_mem = open(proc_mem, O_RDWR);
	if (fd_proc_mem == -1) {
		printf("Could not open %s\n", proc_mem);
		exit(-1);
	}
	char *buf = malloc(len);
	// SEEK_SET 是文件的起始位置，表示将文件指针移动到从起始位置偏移 addr 的位置
	lseek(fd_proc_mem, (__off_t)addr, SEEK_SET);
	// 读取该位置的内容
	read(fd_proc_mem, buf, len);
	printf("String at %p in process %ld is:\n", (void *)addr, pid);
	printf("  %s\n", buf);
	printf("\nNow, this string is modified\n");
	strncpy(buf, "Hello proc-2 world", len);
	// 将文件指针移动到从起始位置偏移 addr 的位置
	lseek(fd_proc_mem, (__off_t)addr, SEEK_SET);
	// 将新内容写入
	if (write(fd_proc_mem, buf, len) == -1) {
		printf("Error while writing\n");
		exit(-1);
	}
	free(buf);
	free(proc_mem);
	return 0;
}
