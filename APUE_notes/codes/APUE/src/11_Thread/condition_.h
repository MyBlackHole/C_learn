/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_cond_t 相关函数的用法
 *
 */
#ifndef CONDITION_
#define CONDITION_
#include<pthread.h>
#include<time.h>

/*!
 * \brief My_pthread_cond_init : 包装了 pthread_cond_init 函数
 * \param cond : 传递给 pthread_cond_init 函数的  cond 参数
 * \param attr : 传递给 pthread_cond_init 函数的  attr 参数
 * \return : 返回 pthread_cond_init 函数的值
 */
int My_pthread_cond_init(pthread_cond_t *cond,const pthread_condattr_t *attr);
/*!
 * \brief My_pthread_cond_destroy : 包装了 pthread_cond_destroy 函数
 * \param cond : 传递给 pthread_cond_destroy 函数的 cond 参数
 * \return : 返回 pthread_cond_destroy 函数的值
 */
int My_pthread_cond_destroy(pthread_cond_t *cond);
/*!
 * \brief My_pthread_cond_wait : 包装了 pthread_cond_wait 函数
 * \param cond : 传递给 pthread_cond_wait 函数的 cond 参数
 * \param mutex : 传递给 pthread_cond_wait 函数的 mutex 参数
 * \return : 返回 pthread_cond_wait 函数的值
 */
int My_pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex);

//int My_pthread_cond_timedwait(pthread_cond_t *cond,pthread_mutex_t *mutex,
//    const struct timespect*tsptr);
/*!
 * \brief My_pthread_cond_signal : 包装了 pthread_cond_signal 函数
 * \param cond : 传递给 pthread_cond_signal 函数的 cond 参数
 * \return : 返回 pthread_cond_signal 函数的值
 */
int My_pthread_cond_signal(pthread_cond_t *cond);
/*!
 * \brief My_pthread_cond_broadcast : 包装了 pthread_cond_broadcast 函数
 * \param cond : 传递给 pthread_cond_broadcast 函数的 cond 参数
 * \return : 返回 pthread_cond_broadcast 函数的值
 */
int My_pthread_cond_broadcast(pthread_cond_t *cond);

/*!
 * \brief test_condition :测试 pthread_cond_t 相关函数的用法
 */
void test_condition();
#endif // CONDITION_

