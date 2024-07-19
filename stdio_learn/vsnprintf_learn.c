/**
 * @file vsnprintf_learn.c
 * @author {BlackHole} ({1358244533@qq.com})
 * @brief
 * @date 2021/08/15 22:18:45
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdarg.h>
#include <stdio.h>

// 该自定义函数，与系统提供的snprintf()函数相同。
int my_snprintf(char *string, int size, const char *fmt, ...)
{
	va_list ap_tmp;
	int num = 0;
	va_start(ap_tmp, fmt); // 获得可变参数列表
	num = vsnprintf(string, size, fmt, ap_tmp); // 写入字符串s
	va_end(ap_tmp); // 释放资源
	return num; // 返回写入的字符个数
}

int demo_vsnprintf_main()
{
	char str[1024];
	my_snprintf(str, sizeof(str), "%d, %d, %d, %d", 5, 6, 7, 8);
	printf("%s\n", str);
	return 0;
}
