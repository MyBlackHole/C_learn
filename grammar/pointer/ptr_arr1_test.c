#include <stdio.h>
#include <stdlib.h>

#define NUM 3

// 数组 与 指针
void test1()
{
	int a_tmp[10];
	int b_tmp[5][10];
	printf("sizeof A=%ld\n", sizeof(a_tmp));
	printf("sizeof B=%ld\n", sizeof(b_tmp));

	int(*pa_tmp) = a_tmp;
	int(*pb_tmp)[10] = b_tmp;
	(void)pa_tmp;
	(void)pb_tmp;
}

// 指针数组空间分配
void test2()
{
	int(*pipes)[2];

	pipes = malloc(NUM * sizeof(*pipes));
	if (pipes == NULL) {
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < NUM; i++) {
		pipes[i][0] = -1;
		pipes[i][1] = -1;
	}

	free(pipes);
}

// void test3() {
//   int (*pipes_bat)[2];
//   pipes_bat = malloc(sizeof(*pipes_bat));
//   if (pipes_bat[0] == NULL) {
//     exit(EXIT_FAILURE);
//   }
//   pipes_bat[1] = malloc(sizeof(int));
//   if (pipes_bat[1] == NULL) {
//     exit(EXIT_FAILURE);
//   }
// }

int demo_ptr_arr1_main(int argc, char *argv[])
{
	test1();
	test2();

	exit(EXIT_SUCCESS);
}
