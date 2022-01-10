/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_detach 函数的用法
 *
 */
#ifndef THREAD_DETACH
#define THREAD_DETACH
#include<pthread.h>

/*!
 * \brief My_pthread_detach : 包装了 pthread_detach 函数
 * \param tid ： 传递给  pthread_detach 函数的  tid 参数
 * \return ： 返回  pthread_detach 参数的值
 */
int My_pthread_detach(pthread_t tid);

/*!
 * \brief test_thread_detach :测试 pthread_detach 函数的用法
 */
void test_thread_detach();
#endif // THREAD_DETACH

