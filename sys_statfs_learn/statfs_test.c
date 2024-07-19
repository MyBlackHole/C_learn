#include <stdio.h>
#include <stdlib.h>
#include <sys/vfs.h>
#include <unistd.h>

int main()
{
	int rv;
	struct statfs diskInfo;

	// statfs("/media/card",&diskInfo);
	// rv = statfs("/dev/test", &diskInfo);
	rv = statfs("/", &diskInfo);
	if (rv != 0) {
		return EXIT_FAILURE;
	}

	// 每个block里面包含的字节数
	unsigned long long blocksize = diskInfo.f_bsize;

	// 总的字节数
	unsigned long long totalsize = blocksize * diskInfo.f_blocks;
	char totalsize_GB[10] = { 0 };

	// 分别换成KB,MB,GB为单位
	printf("TOTAL_SIZE == %llu KB  %llu MB  %llu GB\n", totalsize >> 10,
	       totalsize >> 20, totalsize >> 30);
	sprintf(totalsize_GB, "%.2f", (float)(totalsize >> 20) / 1024);
	printf("totalsize_GB=%s\n", totalsize_GB);

	// 再计算下剩余的空间大小
	unsigned long long freesize = blocksize * diskInfo.f_bfree;

	printf("DISK_FREE == %llu KB  %llu MB  %llu GB\n", freesize >> 10,
	       freesize >> 20, freesize >> 30);

	unsigned long long usedsize =
		blocksize * (diskInfo.f_blocks - diskInfo.f_bfree);
	char usedsize_GB[10] = { 0 };
	sprintf(usedsize_GB, "%.2f", (float)(usedsize >> 20) / 1024);
	printf("usedsize_GB=%s\n", usedsize_GB);

	return EXIT_SUCCESS;
}
