#include <stdio.h>

/*
 * 大端模式，是指数据的高字节保存在内存的低地址中，
 * 而数据的低字节保存在内存的高地址中，
 * 这样的存储模式有点儿类似于把数据当作字符串顺序处理：
 * 地址由小向大增加，而数据从高位往低位放；
 * 这和我们的阅读习惯一致。
 */
/*
 * 小端模式，是指数据的高字节保存在内存的高地址中，
 * 而数据的低字节保存在内存的低地址中，
 * 这种存储模式将地址的高低和数据位权有效地结合起来，
 * 高地址部分权值高，低地址部分权值低。
 */
int demo_union_main()
{
	union number {
		/*定义一个联合*/
		int i;
		struct {
			/*在联合中定义一个结构*/
			char first;
			char second;
		} half;

	} num;

	num.i = 0x4241;
	/*联合成员赋值*/
	printf("%c--%c\n", num.half.first, num.half.second);

	num.half.first = 'a';
	/*联合中结构成员赋值*/
	num.half.second = 'b';
	printf("%x\n", num.i);

	union number b_1;
	(void)b_1;

	getchar();
	return 0;
}
