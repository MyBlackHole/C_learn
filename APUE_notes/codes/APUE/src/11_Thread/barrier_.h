/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_barrier_t 相关函数的用法
 *
 */
#ifndef BARRIER_
#define BARRIER_
#include<pthread.h>

/*!
 * \brief My_pthread_barrier_init : 包装了 pthread_barrier_init 函数
 * \param barrier : 传递给 pthread_barrier_init 函数的 barrier 参数
 * \param attr : 传递给 pthread_barrier_init 函数的 attr 参数
 * \param count : 传递给 pthread_barrier_init 函数的 count 参数
 * \return : 返回 pthread_barrier_init 函数的值
 */
int My_pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, int count);
/*!
 * \brief My_pthread_barrier_destroy : 包装了 pthread_barrier_destroy 函数
 * \param barrier : 传递给 pthread_barrier_destroy 函数的 barrier 参数
 * \return : 返回 pthread_barrier_destroy 函数的值
 */
int My_pthread_barrier_destroy(pthread_barrier_t *barrier);
/*!
 * \brief My_pthread_barrier_wait : 包装了 pthread_barrier_wait 函数
 * \param barrier : 传递给 pthread_barrier_wait 函数的 barrier 参数
 * \return : 返回 pthread_barrier_wait 函数的值
 */
int My_pthread_barrier_wait(pthread_barrier_t * barrier);

/*!
 * \brief test_barrier : 测试 pthread_barrier_t 相关函数的用法
 */
void test_barrier();
#endif // BARRIER_

