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
#include"condition_.h"
#include"../header.h"
int My_pthread_cond_init(pthread_cond_t *cond,const pthread_condattr_t *attr)
{
    int result=pthread_cond_init(cond,attr);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_cond_init(%p,%p) failed,because %s\n",
               pid,cond,attr,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_cond_init(%p,%p) ok\n",
               pid,cond,attr);
    }
    return result;

}
int My_pthread_cond_destroy(pthread_cond_t *cond)
{
    int result=pthread_cond_destroy(cond);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_cond_destroy(%p) failed,because %s\n",
               pid,cond,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_cond_destroy(%p) ok\n",
               pid,cond);
    }
    return result;
}
int My_pthread_cond_wait(pthread_cond_t *cond,pthread_mutex_t *mutex)
{
    int result=pthread_cond_wait(cond,mutex);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_cond_wait(%p,%p) failed,because %s\n",
               pid,cond,mutex,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_cond_wait(%p,%p) ok\n",
               pid,cond,mutex);
    }
    return result;
}

/*!
 * \brief My_pthread_cond_timedwait : 包装了pthread_cond_timedwait  函数
 * \param cond : 传递给 pthread_cond_timedwait  函数的 cond 参数
 * \param mutex : 传递给 pthread_cond_timedwait 函数的 mutex 参数
 * \param tsptr : 传递给 pthread_cond_timedwait 函数的 tsptr 参数
 * \return : 返回 pthread_cond_timedwait 函数的值
 */
int My_pthread_cond_timedwait(pthread_cond_t *cond,pthread_mutex_t *mutex,
    const struct timespect*tsptr)
{
    int result=pthread_cond_timedwait(cond,mutex,tsptr);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_cond_timedwait(%p,%p,%p) failed,because %s\n",
               pid,cond,mutex,tsptr,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_cond_timedwait(%p,%p,%p) ok\n",
               pid,cond,mutex,tsptr);
    }
    return result;
}
int My_pthread_cond_signal(pthread_cond_t *cond)
{
    int result=pthread_cond_signal(cond);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_cond_signal(%p) failed,because %s\n",
               pid,cond,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_cond_signal(%p) ok\n",
               pid,cond);
    }
    return result;
}
int My_pthread_cond_broadcast(pthread_cond_t *cond)
{
    int result=pthread_cond_broadcast(cond);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_cond_broadcast(%p) failed,because %s\n",
               pid,cond,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_cond_broadcast(%p) ok\n",
               pid,cond);
    }
    return result;
}


extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);
extern int My_pthread_mutex_lock(pthread_mutex_t *mutex);
extern int My_pthread_unmutex_lock(pthread_mutex_t *mutex);
extern int My_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
extern int My_pthread_mutex_destroy(pthread_mutex_t *mutex);

/*!
 * \brief mutex : 互斥量
 */
static pthread_mutex_t mutex;
/*!
 * \brief cond : 条件变量
 */
static pthread_cond_t cond;
/*!
 * \brief shared_int : 全局共享数据
 */
static int shared_int;

/*!
 * \brief thread_func_wait : 线程的工作例程，等待条件变量的版本
 * \param arg : 线程参数。这里没有用处
 * \return :返回读到的 shared_int 值
 */
static void* thread_func_wait (void* arg)
{
    My_pthread_mutex_lock(&mutex); // 加锁
    printf("\n****** Begin Thread_wait:thread id=0x%x ******\n",pthread_self());
    My_pthread_cond_wait(&cond,&mutex); // 等待条件发生
    int read_data=shared_int;
    printf("read shared_int :%d.\n",read_data);
    shared_int=read_data*2;
    printf("****** End Thread_wait:thread id=0x%x ******\n\n",pthread_self());
    My_pthread_mutex_unlock(&mutex); // 解锁
    return read_data;
}
/*!
 * \brief thread_func_signal : 线程的工作例程，发送条件变量信号的版本
 * \param arg : 线程参数。这里没有用处
 * \return :返回读到的 shared_int 值
 */
static void* thread_func_signal (void* arg)
{
    My_pthread_mutex_lock(&mutex); // 加锁
    printf("\n****** Begin Thread_signal:thread id=0x%x ******\n",pthread_self());
    int read_data=shared_int;
    printf("read shared_int :%d.\n",read_data);
    shared_int=read_data+3;
    if(shared_int>=3) // 条件发生，则发送信号
    {
        My_pthread_cond_signal(&cond);
    }
    printf("****** End Thread_signal:thread id=0x%x ******\n\n",pthread_self());
    My_pthread_mutex_unlock(&mutex); // 解锁
    return read_data;
}


void test_condition()
{
    M_TRACE("---------  Begin test_condition()  ---------\n");
    //********** 初始化 *************//
    shared_int=0;
    My_pthread_mutex_init(&mutex,NULL);
    My_pthread_cond_init(&cond,NULL);
    //******** 创建子线程 *********//
    const int N=2;

    pthread_t thread_waits[N];
    pthread_t thread_signals[N];

    My_pthread_mutex_lock(&mutex); // 加锁
    for(int i=0;i<N;i++)
        My_pthread_create(thread_waits+i,NULL,thread_func_wait,0); //这些线程都在等待事件的发生
    My_pthread_mutex_unlock(&mutex); // 解锁

    My_pthread_mutex_lock(&mutex); // 加锁
    for(int i=0;i<N;i++)
        My_pthread_create(thread_signals+i,NULL,thread_func_signal,0); //这些线程都在发送事件发生的信号
    My_pthread_mutex_unlock(&mutex); // 解锁
    //******** 等待子线程结束 *********//
    int values[N];
    for(int i=0;i<N;i++)
        thread_join_int(thread_waits[i],values+i);
    for(int i=0;i<N;i++)
        thread_join_int(thread_signals[i],values+i);

    My_pthread_mutex_destroy(&mutex);
    My_pthread_cond_destroy(&cond);
    M_TRACE("---------  End test_condition()  ---------\n\n");
}
