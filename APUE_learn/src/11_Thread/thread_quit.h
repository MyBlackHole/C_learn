/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_join 函数、pthread_exit 函数、 pthread_cancel 函数的用法
 *
 */
#ifndef THREAD_QUIT
#define THREAD_QUIT
#include<pthread.h>

/*!
 * \brief My_pthread_cancel : 包装了 pthread_cancel 函数
 * \param tid : 传递给 pthread_cancel 函数的 tid 参数
 * \return : 返回 pthread_cancel 函数的值
 */
int My_pthread_cancel(pthread_t tid);

/*!
 * \brief test_thread_quit ：测试 pthread_join 函数、pthread_exit 函数、 pthread_cancel 函数
 */
void test_thread_quit();
#endif // THREAD_QUIT

