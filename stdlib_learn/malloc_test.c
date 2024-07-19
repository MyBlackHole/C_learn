#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* C 库函数 void *malloc(size_t size) 分配所需的
 * 存空间，并返回一个指向它的指针。 */
/* void *malloc(size_t size) */
/* size -- 内存块的大小，以字节为单位。 */

int main()
{
	char *str;

	/* 最初的内存分配 */
	str = (char *)malloc(15);
	memset(str, 0, 15);
	strcpy(str, "runoob");
	printf("String = %s,  Address = %p\n", str, str);

	/* 重新分配内存 */
	str = (char *)realloc(str, 25);
	/* memset(str, 0, 25); */
	strcat(str, ".com");
	printf("String = %s,  Address = %p\n", str, str);

	free(str);

	return (0);
}
