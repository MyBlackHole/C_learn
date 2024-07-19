// 使用 glob 递归匹配目录下所有层级文件
// 编译命令：gcc -o glob1_test glob1_test.c -lglob

#include <stdio.h>
#include <glob.h>

int demo_glob1_main()
{
	glob_t globbuf;
	int err = glob("**/*.c", GLOB_MARK, NULL, &globbuf);
	if (err != 0) {
		perror("glob error");
		return 1;
	}
	for (size_t i = 0; i < globbuf.gl_pathc; i++) {
		printf("%s\n", globbuf.gl_pathv[i]);
	}
	globfree(&globbuf);
	return 0;
}
