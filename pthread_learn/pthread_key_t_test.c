#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

static pthread_key_t p_key = 0;

static void func1()
{
	// 同一线程内的各个函数间共享数据
	int *tmp = (int *)pthread_getspecific(p_key);
	printf("%d is runing in %s\n", *tmp, __func__);
}

static void *func2()
{
	// 同一线程内的各个函数间共享数据
	int *tmp = pthread_getspecific(p_key);
	if (tmp == NULL) {
		printf("%s is runing in %s\n", "tmp is NULL", __func__);
		return NULL;
	}
	printf("%d is runing in %s\n", *tmp, __func__);
	return NULL;
}

static void *thread_func(void *args)
{
	pthread_t p_t;
	pthread_setspecific(p_key, args);
	// 获得线程的私有空间
	int *tmp = (int *)pthread_getspecific(p_key);
	printf("%d is runing in %s\n", *tmp, __func__);

	// 修改私有变量的值
	*tmp = (*tmp) * 100;

	func1();
	pthread_create(&p_t, NULL, func2, NULL);
	pthread_join(p_t, NULL);

	return NULL;
}

int demo_pthread_key_t_main()
{
	pthread_t pa_t;
	pthread_t pb_t;
	int int_a = 1;
	int int_b = 2;
	pthread_key_create(&p_key, NULL);
	pthread_create(&pa_t, NULL, thread_func, &int_a);
	pthread_create(&pb_t, NULL, thread_func, &int_b);
	pthread_join(pa_t, NULL);
	pthread_join(pb_t, NULL);
	return EXIT_SUCCESS;
}
