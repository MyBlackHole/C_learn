#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	int a;
	char b;
	bool c;
} my_struct_t;

void func3(my_struct_t *my_struct)
{
	my_struct->c = true;
}

void func2(my_struct_t *my_struct)
{
	my_struct->b = '\0';
	func3(my_struct);
}

void func1(my_struct_t *my_struct)
{
	my_struct->a = 2;
	func2(my_struct);
}

int demo_watch_main()
{
	my_struct_t my_struct = { 1, 'a', false };
	func1(&my_struct);
	exit(EXIT_SUCCESS);
}
