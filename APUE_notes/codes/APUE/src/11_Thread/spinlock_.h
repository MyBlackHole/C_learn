/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_spinlock_t 相关函数的用法
 *
 */
#ifndef SPINLOCK_
#define SPINLOCK_
#include<pthread.h>

/*!
 * \brief My_pthread_spin_init : 包装了 pthread_spin_init 函数
 * \param lock : 传递给 pthread_spin_init 函数的  lock 参数
 * \param pshared : 传递给 pthread_spin_init 函数的 pshared 参数
 * \return : 返回 pthread_spin_init 函数的值
 */
int My_pthread_spin_init(pthread_spinlock_t *lock,int pshared);
/*!
 * \brief My_pthread_spin_destroy : 包装了 pthread_spin_destroy 函数
 * \param lock : 传递给 pthread_spin_destroy 函数的 lock 参数
 * \return : 返回 pthread_spin_destroy 函数的值
 */
int My_pthread_spin_destroy(pthread_spinlock_t *lock);
/*!
 * \brief My_pthread_spin_lock : 包装了 pthread_spin_lock 函数
 * \param lock : 传递给 pthread_spin_lock 函数的 lock 参数
 * \return : 返回 pthread_spin_lock 函数的值
 */
int My_pthread_spin_lock(pthread_spinlock_t *lock);
/*!
 * \brief My_pthread_spin_trylock : 包装了 pthread_spin_trylock 函数
 * \param lock : 传递给 pthread_spin_trylock 函数的 lock 参数
 * \return : 返回 pthread_spin_trylock 函数的值
 */
int My_pthread_spin_trylock(pthread_spinlock_t *lock);
/*!
 * \brief My_pthread_spin_unlock : 包装了 pthread_spin_unlock 函数
 * \param lock : 传递给 pthread_spin_unlock 函数的 lock 参数
 * \return : 返回 pthread_spin_unlock 函数的值
 */
int My_pthread_spin_unlock(pthread_spinlock_t *lock);

/*!
 * \brief test_spinlock : 测试 pthread_spinlock_t 相关函数的用法
 */
void test_spinlock();
#endif // SPINLOCK_

