#include <stdio.h>
#include <strings.h>

/* strcasecmp()用来比较参数__s1 和__s2 字符串，比较时会自动忽略大小写的差异 */
/* 若参数__s1 和__s2 字符串相同则返回0。
 * __s1 长度大于__s2 长度则返回大于0 的值，
 * __s1 长度若小于__s2 长度则返回小于0 的值 */
void func1()
{
	char s[] = "abc";
	int bool = 0;
	bool = strcasecmp(s, "abc");
	printf("%d\n", bool);

	bool = strcasecmp(s, "ab");
	printf("%d\n", bool);
}

int main(int argc, char *argv[])
{
	func1();
}
