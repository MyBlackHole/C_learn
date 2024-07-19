#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 11
int cnt[W];
int b[W];

void count_sort(int *a, int n)
{
	memset(cnt, 0, n * sizeof(int));
	for (int i = 0; i <= n; ++i) {
		++cnt[a[i]];
	}

	for (int i = 0; i <= W; ++i) {
		if (i == 0) {
			printf("%d", cnt[i]);
		} else {
			printf(",%d", cnt[i]);
		}
	}
	printf("\n");

	for (int i = 1; i <= W; ++i) {
		cnt[i] += cnt[i - 1];
	}

	for (int i = 0; i <= W; ++i) {
		if (i == 0) {
			printf("%d", cnt[i]);
		} else {
			printf(",%d", cnt[i]);
		}
	}
	printf("\n");

	for (int i = 0; i <= n; ++i) {
		b[--cnt[a[i]]] = a[i];
	}

	for (int i = 0; i <= n; ++i) {
		a[i] = b[i];
	}
}

int main(int argc, char *argv[])
{
	int a[] = { 1, 4, 6, 2, 0, 8 };
	int count = sizeof(a) / sizeof(int) - 1;
	count_sort(a, count);
	for (int i = 0; i <= count; i++) {
		printf("%d\n", a[i]);
	}
	return EXIT_SUCCESS;
}
