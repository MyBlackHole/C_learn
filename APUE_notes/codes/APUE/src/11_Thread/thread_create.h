/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_equal 函数、pthread_self 函数、 pthread_create 函数的用法
 *
 */
#ifndef THREAD_CREATE
#define THREAD_CREATE

#include<pthread.h>

/*!
 * \brief My_pthread_create : 包装了 pthread_create  函数
 * \param tidp : 传递给  pthread_create  函数的  tidp  参数
 * \param attr : 传递给  pthread_create  函数的 attr   参数
 * \param arg : 传递给  pthread_create  函数的  arg  参数
 * \return ： 返回  pthread_create  函数的值
 */
int My_pthread_create(pthread_t *tidp,const pthread_attr_t *attr,
        void *(*start_rtn)(void*),void *arg);

/*!
 * \brief print_threadid : 打印当前线程的 ID
 */
void print_thread_id();
/*!
 * \brief thread_join_int ： 包装了 pthread_join 函数，但是子返回值为 int
 * \param tid : 线程 ID
 * \param rval_pptr :存放子线程返回值
 */
void thread_join_int(pthread_t tid,int* rval_pptr);
/*!
 * \brief test_thread_create : 测试 pthread_equal 函数、pthread_self 函数、 pthread_create 函数
 */
void test_thread_create();
#endif // THREAD_CREATE

