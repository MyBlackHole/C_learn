#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) a > b ? a : b

int mem[103];

int *a;
int n;

int dfs(int i)
{
	if (mem[i] != -1) {
		return mem[i];
	}
	int ret = 1;
	for (int j = 1; j < i; j++) {
		if (a[j] < a[i]) {
			ret = max(ret, dfs(j) + 1);
		}
	}
	return mem[i] = ret;
}

int main(int argc, char *argv[])
{
	int ret = 0;
	memset(mem, -1, sizeof(mem));

	ret = scanf("%d", &n);
	assert(ret);

	a = malloc(n * sizeof(int));
	assert(a != NULL);

	for (int i = 0; i < n; i++) {
		ret = scanf("%d", &a[i]);
		assert(ret);
	}

	for (int j = 1; j <= n; j++) {
		ret = max(ret, dfs(j));
	}
	printf("%d\n", ret);

	free(a);
	return EXIT_SUCCESS;
}
