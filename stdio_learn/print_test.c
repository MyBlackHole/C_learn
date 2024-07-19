#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_print_test_main(int argc, char *argv[])
{
	int index;
	for (index = 0; index < 3; index++) {
		printf("%.*s%s\n", index, " ", "########");
	}

	// //循环三次
	// 第一次不输出空格
	// 第二次输出一个空格
	// 第三次输出两个空格
	// ########
	//  ########
	//  ########

	// int  int_a, int_b;
	// char char_b[10] = {0};
	// scanf("%d%*s", &int_a, char_b);
	// // 输入为：12abc 那么 12将会读取到变量a中，
	// // 但是后面的abc将在读取之后抛弃，不赋予任何变量(例如这里的字符数组b）
	return EXIT_SUCCESS;
}
