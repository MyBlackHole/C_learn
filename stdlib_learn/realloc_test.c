#include <stdio.h>
#include <stdlib.h>

/* realloc() 函数用来重新分配内存空间，其原型为： */
/*     void* realloc (void* ptr, size_t size); */
/* ptr 为需要重新分配的内存空间指针
 * size 为新的内存空间的大小。 */

/* 指针 ptr 必须是在动态内存空间分配成功的指针，形如如下的指针是不可以的：int
 * *i; int a[2]；会导致运行时错误，可以简单的这样记忆：用
 * malloc()、calloc()、realloc() 分配成功的指针才能被 realloc() 函数接受。 */
/* [成功分配内存后 ptr 将被系统回收]，一定不可再对 ptr 指针做任何操作，包括
 * free()；相反的，可以对 realloc() 函数的返回值进行正常操作。 */
/* 如果是扩大内存操作会把 ptr 指向的内存中的数据复制到新地址（新地址也可
 * 会和原地址相同，但依旧不能对原指针进行任何操作）；如果是缩小内存操作，原始据会被复制并截取新长度。
 */
int main()
{
	int input, n;
	int count = 0;
	int *numbers = NULL;
	int *more_numbers = NULL;

	do {
		printf("Enter an integer value (0 to end): ");
		scanf("%d", &input);
		count++;

		more_numbers = (int *)realloc(numbers, count * sizeof(int));

		if (more_numbers != NULL) {
			numbers = more_numbers;
			numbers[count - 1] = input;
		} else {
			free(numbers);
			puts("Error (re)allocating memory");
			exit(1);
		}
	} while (input != 0);

	printf("Numbers entered: ");
	for (n = 0; n < count; n++) {
		printf("%d ", numbers[n]);
	}
	free(numbers);

	fflush(stdout);
	system("ls");
	return 0;
}
