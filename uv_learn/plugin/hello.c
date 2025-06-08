#include "plugin.h"
//
// 关键的不同是：-Wl,--export-dynamic
// -Wl:指示后面的选项是给链接器的
// --export-dynamic：就是这个选项让主程序内定义的全局函数对库函数可见。
// gcc -g -fPIC hello.c -shared -o libhello.so
// gcc -Wl,--export-dynamic -luv main.c -o main
// ./main ./libhello.so
//
void initialize()
{
	mfp_register("Hello World!");
}
