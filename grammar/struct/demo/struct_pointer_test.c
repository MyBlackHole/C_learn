#include <stdio.h>
#include <stdlib.h>

struct A {
	int a;
	int b;
	char *s[1];
};

int main()
{
	struct A *a;
	a = malloc(sizeof(struct A) + 10 * (sizeof(char *)));
	char *s1 = "cso";
	char *s2 = "osc";
	a->s[0] = s1;
	a->s[9] = s2;
	printf("%s -- %s\n", a->s[0], a->s[9]);

	return 0;
}
