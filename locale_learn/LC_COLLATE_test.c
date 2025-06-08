#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int demo_LC_COLLATE__main(void)
{
	int index;
	char str[10][4] = { "镕", "堃", "趙", "錢", "孫",
			    "李", "周", "吳", "鄭", "王" };
	qsort(str, 10, 4, (__compar_fn_t)strcoll);
	printf("按内码排序：");
	for (index = 0; index < 10; index++) {
		printf("%s", str[index]);
	}

	// 在Windows下请写作 setlocale (LC_ALL,"zh-CN");
	setlocale(LC_COLLATE, "zh_CN");
	qsort(str, 10, 4, (__compar_fn_t)strcoll);
	printf("\n按音序排序：");
	for (index = 0; index < 10; index++) {
		printf("%s", str[index]);
	}

	printf("\n");
	return EXIT_SUCCESS;
}
