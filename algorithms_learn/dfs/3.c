#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tcost[103], mget[103];
int ans = 0;
int n, t;

void dfs(int pos, int tleft, int tans)
{
	if (tleft < 0) {
		return;
	}
	if (pos == n + 1) {
		ans = ans > tans ? ans : tans;
		return;
	}

	// 经过一个节点就只有一下两种可能
	dfs(pos + 1, tleft, tans);
	dfs(pos + 1, tleft - tcost[pos], tans + mget[pos]);
}

// 优化
// 避免同一状态被访问多次
int mem[103][1003];

// 求 pos 至 n 当时间等于 tleft 的最大值
int dfs_(int pos, int tleft)
{
	if (mem[pos][tleft] != -1) {
		// 已经访问过的状态，直接返回之前记录的值
		printf("pos:%d tleft:%d\n", pos, tleft);
		return mem[pos][tleft];
	}
	if (pos == n + 1) {
		return mem[pos][tleft] = 0;
	}
	int dfs1, dfs2 = INT_MIN;
	dfs1 = dfs_(pos + 1, tleft);
	if (tleft >= tcost[pos]) {
		// 状态转移
		dfs2 = dfs_(pos + 1, tleft - tcost[pos]) + mget[pos];
	}
	// 最后将当前状态的值存下来
	return mem[pos][tleft] = dfs1 > dfs2 ? dfs1 : dfs2;
}

// 遍历出一个关于 i,j 的二维数组最优值
void recursive()
{
	int mij = 0, mi1jmii = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= t; j++) {
			mem[i][j] = mem[i - 1][j];
			if (j >= tcost[i]) {
				mij = mem[i][j];
				mi1jmii = mem[i - 1][j - tcost[i]] + mget[i];
				// 状态转移方程
				mem[i][j] = mij > mi1jmii ? mij : mi1jmii;
			}
		}
	}
	printf("%d\n", mem[n][t]);
}

int main(int argc, char *argv[])
{
	int ret;
	ret = scanf("%d %d", &t, &n);
	assert(ret == 2);
	for (int i = 1; i <= n; i++) {
		ret = scanf("%d %d", &tcost[i], &mget[i]);
		assert(ret == 2);
	}
	// dfs(1, t, 0);
	// printf("%d\n", ans);

	// memset(mem, -1, sizeof(mem));
	// printf("%d\n", dfs_(1, t));

	recursive();

	return EXIT_SUCCESS;
}
