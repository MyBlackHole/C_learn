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
#include"thread_quit.h"
#include"../header.h"

extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);

int My_pthread_cancel(pthread_t tid)
{
    int result=pthread_cancel(tid);
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_cancel(0x%x) failed,because %s\n",
               pthread_self(),tid,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_cancel(0x%x) ok\n",
               pthread_self(),tid);
    }
    return result;
}

/*!
 * \brief mutex : 互斥量，每个线程用它来完成串行工作
 */
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
/*!
 * \brief thread_func_return : 线程的工作例程，该线程通过 return 返回
 * \param arg : 参数，这里是个整数
 * \return :直接返回参数
 */
static void* thread_func_return (void* arg)
{
    pthread_mutex_lock(&mutex); //必须同步。否则多个线程的输出交叉进行
    printf("\n****** Begin Thread_Return:thread id=0x%x ******\n",pthread_self());
    printf("arg is %d\n",arg);
    printf("****** End Thread_Return:thread id=0x%x ******\n\n",pthread_self());
    pthread_mutex_unlock(&mutex);
    return arg;
}
/*!
 * \brief thread_func_exit : 线程的工作例程，该线程通过 pthread_exit 返回
 * \param arg : 参数，这里是个整数
 */
static void* thread_func_exit (void* arg)
{
    pthread_mutex_lock(&mutex); //必须同步。否则多个线程的输出交叉进行
    printf("\n****** Begin Thread_Exit:thread id=0x%x ******\n",pthread_self());
    printf("arg is %d\n",arg);
    sleep(3); //确保主线程运行到 pthread_cancel 时，子线程并没有结束
    printf("****** End Thread_Exit:thread id=0x%x ******\n\n",pthread_self());
    pthread_mutex_unlock(&mutex);
    pthread_exit(arg);
}

void test_thread_quit()
{
    M_TRACE("---------  Begin test_thread_quit()  ---------\n");
    //******** 创建子线程 *********//
    pthread_mutex_lock(&mutex); //必须同步。否则多个线程的输出交叉进行
    pthread_t threads[3];
    My_pthread_create(threads+0,NULL,thread_func_return,(void*)0);
    My_pthread_create(threads+1,NULL,thread_func_exit,(void*)1);
    My_pthread_create(threads+2,NULL,thread_func_exit,(void*)2);
    pthread_mutex_unlock(&mutex);
    My_pthread_cancel(threads[2]) ; // 取消最后一个子线程
    //******** 等待子线程结束 *********//
    int values[3];
    for(int i=0;i<3;i++)
    {
        thread_join_int(threads[i],values+i);
    }
    M_TRACE("---------  End test_thread_quit()  ---------\n\n");
}
