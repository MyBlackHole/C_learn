#include <stdio.h>
#include <string.h>

/* 在重叠内存块这方面，memmove() 是比 memcpy() 更安全的方法 */
/* str1 -- 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。 */
/* str2 -- 指向要复制的数据源，类型强制转换为 void* 指针。 */
/* n -- 要被复制的字节数。 */
/* void *memmove(void *str1, const void *str2, size_t n) */
int demo_memmove_test_main()
{
	const char dest[] = "oldstring";
	const char src[] = "newstring";

	printf("Before memmove dest = %s, src = %s\n", dest, src);
	memmove((void *)dest, (void *)src, 9);
	printf("After memmove dest = %s, src = %s\n", dest, src);

	return (0);
}
