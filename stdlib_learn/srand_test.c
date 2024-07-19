#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 初始化随机数发生器 */
/* void srand(unsigned int seed) */

/* seed -- 这是一个整型值，用于伪随机数生成算法播种。 */

int main()
{
	int i, n;
	time_t t;

	n = 5;

	srand((unsigned)time(&t));

	for (i = 0; i < n; i++) {
		printf("%d\n", rand() * 50);
	}

	return 0;
}
