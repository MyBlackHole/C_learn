/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_mutex_t 相关函数的用法
 *
 */
#ifndef MUTEX_
#define MUTEX_

#include<pthread.h>
#include<time.h>

/*!
 * \brief My_pthread_mutex_init : 包装了 pthread_mutex_init 函数
 * \param mutex : 传递给 pthread_mutex_init 函数的  mutex 参数
 * \param attr : 传递给 pthread_mutex_init 函数的 attr 参数
 * \return : 返回 pthread_mutex_init 函数的值
 */
int My_pthread_mutex_init(pthread_mutex_t *mutex,
        const pthread_mutexattr_t *attr);
/*!
 * \brief My_pthread_mutex_destroy : 包装了 pthread_mutex_destroy 函数
 * \param mutex : 传递给 pthread_mutex_destroy 函数的 mutex 参数
 * \return : 返回 pthread_mutex_destroy 函数的值
 */
int My_pthread_mutex_destroy(pthread_mutex_t *mutex);
/*!
 * \brief My_pthread_mutex_lock : 包装了 thread_mutex_lock 函数
 * \param mutex : 传递给 thread_mutex_lock 函数的 mutex 参数
 * \return : 返回 thread_mutex_lock 函数的值
 */
int My_pthread_mutex_lock(pthread_mutex_t *mutex);
/*!
 * \brief My_pthread_mutex_trylock : 包装了 pthread_mutex_trylock 函数
 * \param mutex : 传递给 pthread_mutex_trylock 函数的 mutex 参数
 * \return : 返回 pthread_mutex_trylock 函数的值
 */
int My_pthread_mutex_trylock(pthread_mutex_t *mutex);
/*!
 * \brief My_pthread_mutex_unlock : 包装了 pthread_mutex_unlock 函数
 * \param mutex : 传递给 pthread_mutex_unlock 函数的 mutex 参数
 * \return : 返回 pthread_mutex_unlock 函数的值
 */
int My_pthread_mutex_unlock(pthread_mutex_t *mutex);
/*!
 * \brief My_pthread_mutex_timedlock : 包装了 pthread_mutex_timedlock 函数
 * \param mutex : 传递给 pthread_mutex_timedlock 函数的 mutex 参数
 * \param tsptr : 传递给 pthread_mutex_timedlock 函数的 tsptr 参数
 * \return : 返回 pthread_mutex_timedlock 函数的值
 */
int My_pthread_mutex_timedlock(pthread_mutex_t *mutex,
        const struct timespec * tsptr);

/*!
 * \brief rel_to_abs_time : 相对时间转换为绝对时间
 * \param seconds ：相对于当前时间的秒数
 * \return ：存放绝对时间的 timespec 结构的指针；如果失败则返回 NULL
 */
struct timespec* rel_to_abs_time(int seconds);

/*!
 * \brief test_mutex : 测试 pthread_mutex_t 相关函数的用法
 */
void test_mutex();
#endif // MUTEX_

