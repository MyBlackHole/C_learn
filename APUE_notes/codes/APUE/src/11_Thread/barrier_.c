/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_barrier_t 相关函数的用法
 *
 */
#include"barrier_.h"
#include"../header.h"

int My_pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, int count)
{
    int result=pthread_barrier_init(barrier,attr,count);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_barrier_init(%p,%p,%d) failed,because %s\n",
               pid,barrier,attr,count,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_barrier_init(%p,%p,%d) ok\n",
               pid,barrier,attr,count);
    }
    return result;
}
int My_pthread_barrier_destroy(pthread_barrier_t *barrier)
{
    int result=pthread_barrier_destroy(barrier);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_barrier_destroy(%p) failed,because %s\n",
               pid,barrier,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_barrier_destroy(%p) ok\n",
               pid,barrier);
    }
    return result;
}
int My_pthread_barrier_wait(pthread_barrier_t * barrier)
{
    int result=pthread_barrier_wait(barrier);
    pid_t pid=pthread_self();
    if(PTHREAD_BARRIER_SERIAL_THREAD==result)
    {
        printf("thread(0x%x) call pthread_barrier_wait(%p) ok,it is the last one\n", // 这是最后一个到达的线程
               pid,barrier);
    }
    else if(0!=result)
    {
        printf("thread(0x%x) call pthread_barrier_wait(%p) failed,because %s\n",
               pid,barrier,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_barrier_wait(%p) ok\n",
               pid,barrier);
    }
    return result;
}


extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);

/*!
 * \brief barrier : 屏障
 */
static pthread_barrier_t barrier;

/*!
 * \brief thread_func : 线程的工作例程
 * \param arg : 参数，这里没有用处
 * \return :0
 */
static void* thread_func (void* arg)
{
    pthread_t id=pthread_self();
    printf("\n****** Begin Thread:thread id=0x%x ******\n",id);
    printf("\n In thread(0x%x),pre barrier:step 1\n",id);
    printf("\n In thread(0x%x),pre barrier:step 2\n",id);
    My_pthread_barrier_wait(&barrier);
    printf("\n In thread(0x%x),post barrier:step 1\n",id);
    printf("\n In thread(0x%x),post barrier:step 2\n",id);
    printf("****** End Thread:thread id=0x%x ******\n\n",id);
    return 0;
}


void test_barrier()
{
    M_TRACE("---------  Begin test_barrier()  ---------\n");
    const int N=3;
    //********** 初始化 *************//
    My_pthread_barrier_init(&barrier,NULL,N);
    //******** 创建子线程 *********//
    pthread_t threads[N];
    for(int i=0;i<N;i++)
        My_pthread_create(threads+i,NULL,thread_func,0);
    //******** 等待子线程结束 *********//
    int values[N];
    for(int i=0;i<N;i++)
        thread_join_int(threads[i],values+i);

    My_pthread_barrier_destroy(&barrier);
    M_TRACE("---------  End test_barrier()  ---------\n\n");
}
