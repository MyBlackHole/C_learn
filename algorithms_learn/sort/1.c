#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *a, int n)
{
	for (int i = 1; i < n; ++i) {
		int ith = i;

		for (int j = i + 1; j <= n; ++j) {
			if (a[j] < a[ith]) {
				ith = j;
			}
		}

		int swap = a[i];
		a[i] = a[ith];
		a[ith] = swap;
	}
}

int main(int argc, char *argv[])
{
	int a[] = { 1, 4, 6, 2, 0, 8 };
	int count = sizeof(a) / sizeof(int) - 1;
	selection_sort(a, count);
	for (int i = 1; i <= count; i++) {
		printf("%d\n", a[i]);
	}
	return EXIT_SUCCESS;
}
