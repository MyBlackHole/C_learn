/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_rwlock_t 相关函数的用法
 *
 */
#ifndef RWLOCK_
#define RWLOCK_
#include<time.h>
#include<pthread.h>

/*!
 * \brief My_pthread_rwlock_init  : 包装了 pthread_rwlock_init   函数
 * \param rwlock : 传递给 pthread_rwlock_init   函数的  rwlock 参数
 * \param attr : 传递给 pthread_rwlock_init   函数的  attr 参数
 * \return : 返回 pthread_rwlock_init   函数的值
 */
int My_pthread_rwlock_init(pthread_rwlock_t *rwlock,
        const pthread_rwlockattr_t *attr);
/*!
 * \brief My_pthread_rwlock_destroy : 包装了 pthread_rwlock_destroy   函数
 * \param rwlock : 传递给 pthread_rwlock_destroy   函数的  rwlock 参数
 * \return : 返回 pthread_rwlock_destroy   函数的值
 */
int My_pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
/*!
 * \brief My_pthread_rwlock_rdlock : 包装了 pthread_rwlock_rdlock   函数
 * \param rwlock : 传递给 pthread_rwlock_rdlock   函数的  rwlock 参数
 * \return : 返回 pthread_rwlock_rdlock   函数的值
 */
int My_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
/*!
 * \brief My_pthread_rwlock_wrlock : 包装了 pthread_rwlock_wrlock   函数
 * \param rwlock : 传递给 pthread_rwlock_wrlock   函数的  rwlock 参数
 * \return : 返回 pthread_rwlock_wrlock   函数的值
 */
int My_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
/*!
 * \brief My_pthread_rwlock_unlock : 包装了 pthread_rwlock_unlock   函数
 * \param rwlock : 传递给 pthread_rwlock_unlock   函数的  rwlock 参数
 * \return : 返回 pthread_rwlock_unlock   函数的值
 */
int My_pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
/*!
 * \brief My_pthread_rwlock_tryrdlock : 包装了 pthread_rwlock_tryrdlock   函数
 * \param rwlock : 传递给 pthread_rwlock_tryrdlock   函数的  rwlock 参数
 * \return : 返回 pthread_rwlock_tryrdlock   函数的值
 */
int My_pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
/*!
 * \brief My_pthread_rwlock_trywrlock : 包装了 pthread_rwlock_trywrlock   函数
 * \param rwlock : 传递给 pthread_rwlock_trywrlock   函数的  rwlock 参数
 * \return : 返回 pthread_rwlock_trywrlock   函数的值
 */
int My_pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
///*!
// * \brief My_pthread_rwlock_timedrdlock : 包装了 pthread_rwlock_timedrdlock   函数
// * \param rwlock : 传递给 pthread_rwlock_timedrdlock   函数的  rwlock 参数
// * \param tsptr : 传递给 pthread_rwlock_timedrdlock   函数的  tsptr 参数
// * \return : 返回 pthread_rwlock_timedrdlock   函数的值
// */
//int My_pthread_rwlock_timedrdlock(pthread_rwlock_t *rwlock,const struct timespect* tsptr);
///*!
// * \brief My_pthread_rwlock_timedwrlock : 包装了 pthread_rwlock_timedwrlock   函数
// * \param rwlock : 传递给 pthread_rwlock_timedwrlock   函数的  rwlock 参数
// * \param tsptr : 传递给 pthread_rwlock_timedwrlock   函数的  tsptr 参数
// * \return : 返回 pthread_rwlock_timedwrlock   函数的值
// */
//int My_pthread_rwlock_timedwrlock(pthread_rwlock_t *rwlock,const struct timespect* tsptr);
/*!
 * \brief test_rwlock :测试 pthread_rwlock_t 相关函数的用法
  */
void test_rwlock();
#endif // RWLOCK_

