#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// 对 a+ 无效
// 1) 欲将读写位置移动到文件开头时:fseek(FILE *stream, 0, SEEK_SET);
// 2) 欲将读写位置移动到文件尾时:fseek(FILE *stream, 0, 0SEEK_END);
// SEEK_SET 从距文件开头offset 位移量为新的读写位置. SEEK_CUR
// 以目前的读写位置往后增加offset 个位移量. SEEK_E
// D
// 将读写位置指向文件尾后再增加offset 个位移量. 当whence 值为SEEK_CUR 或
// SEEK_END 时, 参数offset 允许负值的出现.

int demo_fseek_main(int argc, char *argv[])
{
	size_t ret = 0;
	FILE *file_p = NULL;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(1);
	}

	file_p = fopen(argv[1], "r+");
	if (file_p == NULL) {
		perror("fopen()");
		exit(1);
	}

	// ret = fseek(file_p, 2, SEEK_SET);
	// // ret = fseek(file_p, -2, SEEK_END);
	// if (ret != 0)
	// {
	//     perror("fseek()");
	//     exit(1);
	// }

	// ret = fwrite("ppppp", 5, 1, file_p);
	// if (ret <= 0)
	// {
	//     perror("fwrite()");
	//     exit(1);
	// }

	// ret = fseek(file_p, 0, SEEK_SET);
	ret = fseek(file_p, 2, SEEK_SET);
	// ret = fseek(file_p, 0, SEEK_END);
	if (ret != 0) {
		perror("fseek()");
		exit(1);
	}

	ret = fwrite("ccc", 3, 1, file_p);
	if (ret <= 0) {
		perror("fwrite()");
		exit(1);
	}

	fprintf(stdout, "count %ld\n", ftell(file_p));

	fclose(file_p);

	exit(0);
}
