/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_cleanup_push 函数、pthread_cleanup_pop 函数的用法
 *
 */

#include"thread_clean.h"
#include"../header.h"
#include<pthread.h>
extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);

/*!
 * \brief clean_func : 线程清理函数
 * \param arg : 线程清理函数的参数
 */
static void clean_func(void* arg)
{
    printf("clearn_up with arg %d\n",arg);
}
/*!
 * \brief thread_func : 线程的工作例程
 * \param arg : 参数，这里是个整数
 * \return :直接返回参数
 */
static void* thread_func (void* arg)
{
    printf("\n****** Begin Thread:thread id=0x%x ******\n",pthread_self());
    printf("arg is %d\n",arg);
    pthread_cleanup_push(clean_func,(int)arg-2 ); // 第一次注册
    pthread_cleanup_push(clean_func,(int)arg-1 ); // 第二次注册
    pthread_cleanup_push(clean_func,(int)arg+1 ); // 第三次注册
    printf("-- 0 --\n");
    pthread_cleanup_pop(0); // 对应第三次注册
    printf("-- 1 --\n");
    pthread_cleanup_pop(1); // 对应第二次注册
    printf("-- 2 --\n");
    pthread_cleanup_pop(2); // 对应第一次注册
    printf("****** End Thread:thread id=0x%x ******\n\n",pthread_self());
    return arg;
}

void test_thread_clean()
{
    M_TRACE("---------  Begin test_thread_clean()  ---------\n");
    //******** 创建子线程 *********//
    pthread_t thread;
    My_pthread_create(&thread,NULL,thread_func,100);
    //******** 等待子线程结束 *********//
    int value;
    thread_join_int(thread,&value);
    M_TRACE("---------  End test_thread_clean()  ---------\n\n");
}
