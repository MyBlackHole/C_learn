#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	char name[10] = { 0 };
	char name1[10] = "aaaaaa";
	strcpy(name, argv[1]);
	printf("%s %p, %s, %p\n", name, name, name1, name1);
	return 0;
}

// Output:
//
// gcc -o a.out test.c
//
// ❯ ./a.out bbbbbbbbbb
// bbbbbbbbbb 0x7ffe0291ce84, , 0x7ffe0291ce8e
// 11
// ❯ ./a.out bbbbbbbbb
// bbbbbbbbb 0x7ffeb43f57f4, aaaaaa, 0x7ffeb43f57fe
// 11
