/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_join 函数的用法
 *
 */
#include"thread_join.h"
#include"../header.h"
#include<pthread.h>

extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);

/*!
 * \brief mutex : 互斥量，每个线程用它来完成串行工作
 */
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
/*!
 * \brief threads : 存放主线程ID和三个子线程ID
 */
static pthread_t threads[4];
/*!
 * \brief thread_func : 线程的工作例程
 * \param arg : 参数，这里是个整数
 * \return :直接返回参数
 */
static void* thread_func (void* arg)
{
    pthread_mutex_lock(&mutex); //必须同步。否则多个线程的输出交叉进行
    printf("\n****** Begin Thread:thread id=0x%x ******\n",pthread_self());
    printf("arg is %d\n",arg);
    printf("****** End Thread:thread id=0x%x ******\n\n",pthread_self());
    pthread_mutex_unlock(&mutex);

    //***** 倒数第二个子线程 join  最后一个子线程 ****//
    if(pthread_equal(pthread_self(),threads[2]))
    {
        int rval=0;
        thread_join_int(threads[3],&rval);
    }
    //***** 倒数第一个子线程 join  主线程 ****//
    if(pthread_equal(pthread_self(),threads[1]))
    {
        int rval=0;
        thread_join_int(threads[0],&rval);
    }
    sleep(2);// 让子线程存续时间足够长
    return arg;
}


void test_thread_join()
{
    M_TRACE("---------  Begin test_thread_join()  ---------\n");
    //******** 创建子线程 *********//
    pthread_mutex_lock(&mutex); //必须同步。否则多个线程的输出交叉进行
    threads[0]=pthread_self();
    for(int i=0;i<3;i++)
        My_pthread_create(threads+i+1,NULL,thread_func,i);
    pthread_mutex_unlock(&mutex);
    //******** 等待子线程结束 *********//
    int values[3];
    for(int i=0;i<2;i++)
    {
        thread_join_int(threads[2+i],values+i);
    }
    M_TRACE("---------  End test_thread_join()  ---------\n\n");
}
