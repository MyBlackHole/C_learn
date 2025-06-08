#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define OPERATE 3

void difference(int *n_data, int n, int **m_data, int m)
{
	int *diff = malloc(n * sizeof(int));
	assert(diff);
	// 计算一维差分数组
	diff[0] = n_data[0];
	for (int i = 1; i < n; i++) {
		diff[i] = n_data[i] - n_data[i - 1];
	}

	// 变更
	for (int i = 0; i < m; i++) {
		diff[m_data[i][0] - 1] += m_data[i][2];
		diff[m_data[i][1]] -= m_data[i][2];
	}

	// 更新 n_data
	n_data[0] = diff[0];
	for (int i = 1; i < n; i++) {
		n_data[i] = n_data[i - 1] + diff[i];
	}

	free(diff);
}

int main(int argc, char *argv[])
{
	int n, m;
	int ret;
	ret = scanf("%d%d", &n, &m);
	assert(ret);

	// 内存申请
	int *n_data = malloc(n * sizeof(int));
	assert(n_data);

	int **m_data = malloc(m * sizeof(int *));
	assert(m_data);

	for (int i = 0; i < n; i++) {
		ret = scanf("%d", n_data + i);
		assert(ret);
	}

	for (int i = 0; i < m; i++) {
		int *m_data_ = malloc(OPERATE * sizeof(int));
		assert(m_data_);
		m_data[i] = m_data_;
		ret = scanf("%d%d%d", m_data_ + 0, m_data_ + 1, m_data_ + 2);
		assert(ret);
	}

	difference(n_data, n, m_data, m);
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			printf("%d", n_data[i]);
		} else {
			printf(",%d", n_data[i]);
		}
	}
	printf("\n");

	// 内存释放
	free(n_data);
	for (int i = 0; i < m; i++) {
		free(m_data[i]);
	}
	free(m_data);

	return EXIT_SUCCESS;
}
