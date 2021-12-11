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
#include"thread_create.h"
#include"../header.h"

int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg)
{
    int result=pthread_create(tidp,attr,start_rtn,arg);
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_create failed,because %s\n",
               pthread_self(),strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_create ok,new thread id is 0x%x\n",
               pthread_self(),*tidp);
    }
    return result;
}

void print_thread_id()
{
    printf("current thread id is 0x%x\n",pthread_self());
}
void thread_join_int(pthread_t tid, int *rval_pptr)
{
    int val=pthread_join(tid,rval_pptr);
    if(0!=val)
    {
        printf("thread 0x%x call pthread_join(0x%x,%p) failed,because %s\n",
               pthread_self(),tid,rval_pptr,strerror(val));
    }else
    {
        if(NULL==rval_pptr)
            printf("thread 0x%x call pthread_join(0x%x,%p) ok\n"
                   ,pthread_self(),tid,rval_pptr);
        else
            printf("thread 0x%x call pthread_join(0x%x,%p) ok,thread returns %d\n"
               ,pthread_self(),tid,rval_pptr,*rval_pptr);
    }
}

/*!
 * \brief mutex : 互斥量，每个线程用它来完成串行工作
 */
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
/*!
 * \brief thread_func : 线程的工作例程
 * \param arg : 参数，这里是个整数
 * \return :直接返回参数
 */
static void* thread_func (void* arg)
{
    pthread_mutex_lock(&mutex); //必须同步。否则多个线程的输出交叉进行
    printf("\n****** Begin Thread:thread id=0x%x ******\n",pthread_self());
    print_thread_id();
    printf("arg is %d\n",arg);
    printf("****** End Thread:thread id=0x%x ******\n\n",pthread_self());
    pthread_mutex_unlock(&mutex);
    return arg;
}
void test_thread_create()
{
    M_TRACE("---------  Begin test_thread_create()  ---------\n");
    //******** 创建子线程 *********//
    pthread_mutex_lock(&mutex); //必须同步。否则多个线程的输出交叉进行
    pthread_t threads[3];
    for(int i=0;i<3;i++)
        My_pthread_create(threads+i,NULL,thread_func,i);
     pthread_mutex_unlock(&mutex);
    //******** 等待子线程结束 *********//
    int values[3];
    for(int i=0;i<3;i++)
    {
        thread_join_int(threads[i],values+i);
    }
    M_TRACE("---------  End test_thread_create()  ---------\n\n");
}
