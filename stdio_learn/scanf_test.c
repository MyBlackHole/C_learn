#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int demo_scanf_main(int argc, char *argv[])
{
	int input_str;
	int status;
	printf("请输入数字\n");
	status = scanf("%d", &input_str);
	assert(status);
	if (!status) {
		perror("scanf 失败");
		exit(EXIT_FAILURE);
	}
	printf("%d\n", input_str);
	printf("status:[%d]\n", status);
	return EXIT_SUCCESS;
}
