//
// Created by Black Hole on 2020/11/2.
//

#include <stdarg.h>
#include <stdio.h>

#define MAXLINE 2048

void print_ferror(const char *format, ...);

int demo_args_main()
{
	print_ferror("Error");
	return 0;
}

void print_ferror(const char *format, ...)
{
	char buf[MAXLINE];
	va_list args;
	va_start(args, format);
	vsnprintf(buf, MAXLINE, format, args);
	perror(buf);
	va_end(args);
}
