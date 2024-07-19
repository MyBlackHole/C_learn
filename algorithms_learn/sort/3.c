#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void insert_sort(int *a, int n)
{
	for (int i = 1; i <= n; ++i) {
		int z = a[i];
		int j = i - 1;
		while (j >= 0 && a[j] > z) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = z;
	}
}

int main(int argc, char *argv[])
{
	int a[] = { 1, 4, 6, 2, 0, 8 };
	int count = sizeof(a) / sizeof(int) - 1;
	insert_sort(a, count);
	for (int i = 0; i <= count; i++) {
		printf("%d\n", a[i]);
	}
	return EXIT_SUCCESS;
}
