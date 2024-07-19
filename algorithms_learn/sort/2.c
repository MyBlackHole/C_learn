#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *a, int n)
{
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 0; i < n; ++i) {
			if (a[i] > a[i + 1]) {
				flag = true;
				int swap = a[i];
				a[i] = a[i + 1];
				a[i + 1] = swap;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	int a[] = { 1, 4, 6, 2, 0, 8 };
	int count = sizeof(a) / sizeof(int) - 1;
	bubble_sort(a, count);
	for (int i = 0; i <= count; i++) {
		printf("%d\n", a[i]);
	}
	return EXIT_SUCCESS;
}
