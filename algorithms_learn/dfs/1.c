#include <stdio.h>
#include <stdlib.h>

int m, arr[103]; // arr 用于记录方案

void dfs(int n, int i, int a)
{
	if (n == 0) {
		for (int j = 1; j <= i - 1; ++j)
			printf("%d ", arr[j]);
		printf("\n");
	}
	if (i <= m) {
		for (int j = a; j <= n; ++j) {
			arr[i] = j;
			dfs(n - j, i + 1, j); // 请仔细思考该行含义。
		}
	}
}

int main(int argc, char *argv[])
{
	int n, m;
	scanf("%d%d", &n, &m);
	dfs(n, 1, 1);
	return EXIT_SUCCESS;
}
