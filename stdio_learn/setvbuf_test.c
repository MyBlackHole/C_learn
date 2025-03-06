#include <stdio.h>
#include <stdlib.h>

int demo_setvbuf_main()
{
	FILE *fp = fopen("example.txt", "w");
	if (fp == NULL) {
		perror("Failed to open file");
		return EXIT_FAILURE;
	}

	// 设置缓冲区大小为 4096 字节，使用全缓冲模式
	// 如果 buffer 设为 NULL，库会自动分配内存
	int result = setvbuf(fp, NULL, _IOFBF, 1024 * 1024 * 100);
	/*int result = setvbuf(fp, NULL, _IOFBF, 4096);*/
	if (result != 0) {
		perror("setvbuf failed");
		fclose(fp);
		return EXIT_FAILURE;
	}

	// 写入数据（会先填充缓冲区，满 4096 字节后自动刷新）
	for (int i = 0; i < 1000; i++) {
		fprintf(fp, "Line %d\n", i);
	}

	fclose(fp);
	return EXIT_SUCCESS;
}
