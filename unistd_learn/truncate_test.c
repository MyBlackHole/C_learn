#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// 文件截取
int demo_truncate_main(int argc, char *argv[])
{
	char *filename = argv[1];
	int length = atoi(argv[2]);
	// length 超过文件原长度零填充，小于文件原长度截断保留 length
	// 文件最终长度都是 length
	truncate(filename, length);
	return EXIT_SUCCESS;
}
