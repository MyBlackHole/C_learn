#include <mcheck.h>
#include <stdio.h>
#include <stdlib.h>

// 也可以这样直接监控
// mtrace /bin/python3

// mtrace是類似malloc_hook的malloc handler
// 只不過mtrace的handlerfunction已由系統爲你寫好，但既然如此，系統又怎麼知道你想將malloc/free的記錄寫在哪裏呢？爲此，調用mtrace()前要先設置MALLOC_TRACE環境變量
int main()
{
	setenv("MALLOC_TRACE", "1.txt", 1);
	// 通过对内存管理系列函数(malloc，realloc，memalign，free)注册钩子来达到监控内存泄露和其他内存错误操作
	mtrace();
	int index;
	void *void_p[10];
	void *int_p;

	for (index = 0; index < 10; index++) {
		void_p[index] = malloc(sizeof(int) * 10);
	}

	// 会清零
	int_p = calloc(sizeof(int), sizeof(long int));
	(void)int_p;

	for (index = 0; index < 10; index++) {
		free(void_p[index]);
	}

	// 解除mtrace注册的钩子
	muntrace();
	exit(EXIT_SUCCESS);
}
