#include <stdio.h>

// 缓冲区的作用: 合并系统调用
// 行缓冲: 换行时刷新, 满了的时候刷新, 强制刷新 (标准输出是这样的, 终端类型)
// 全缓冲: 满了时刷新, 强制刷新 (默认,只要不是终端)
// 无缓冲: 例如stderr, 需要立即输出的内容
// setvbuf

int demo_fflush_main(int argc, char *argv[])
{
	// // \n触发刷新
	// printf("Before while()\n");

	printf("Before while()\n");
	// 没有这句将永远不会输出
	fflush(stdout);
	while (1) {
		;
	}
	printf("After while()\n");
	return 0;
}
