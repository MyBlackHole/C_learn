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
#include"spinlock_.h"
#include"../header.h"
int My_pthread_spin_init(pthread_spinlock_t *lock,int pshared)
{
    int result=pthread_spin_init(lock,pshared);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_spin_init(%p,%d) failed,because %s\n",
               pid,lock,pshared,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_spin_init(%p,%d) ok\n",
               pid,lock,pshared);
    }
    return result;
}
int My_pthread_spin_destroy(pthread_spinlock_t *lock)
{
    int result=pthread_spin_destroy(lock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_spin_destroy(%p) failed,because %s\n",
               pid,lock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_spin_destroy(%p) ok\n",
               pid,lock);
    }
    return result;
}
int My_pthread_spin_lock(pthread_spinlock_t *lock)
{
    int result=pthread_spin_lock(lock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_spin_lock(%p) failed,because %s\n",
               pid,lock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_spin_lock(%p) ok\n",
               pid,lock);
    }
    return result;
}
int My_pthread_spin_trylock(pthread_spinlock_t *lock)
{
    int result=pthread_spin_trylock(lock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_spin_trylock(%p) failed,because %s\n",
               pid,lock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_spin_trylock(%p) ok\n",
               pid,lock);
    }
    return result;
}
int My_pthread_spin_unlock(pthread_spinlock_t *lock)
{
    int result=pthread_spin_unlock(lock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_spin_unlock(%p) failed,because %s\n",
               pid,lock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_spin_unlock(%p) ok\n",
               pid,lock);
    }
    return result;
}

extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);
/*!
 * \brief shared_int : 全局共享数据
 */
static int shared_int;
/*!
 * \brief spin_lock : 自旋锁
 */
static pthread_spinlock_t spin_lock;

/*!
 * \brief thread_func : 线程的工作例程
 * \param arg : 参数，这里没有用处
 * \return :返回读到的 shared_int 值
 */
static void* thread_func (void* arg)
{
    My_pthread_spin_lock(&spin_lock);// 加锁
    printf("\n****** Begin Thread:thread id=0x%x ******\n",pthread_self());
    int read_data=shared_int;
    printf("read shared_int :%d.\n",read_data);
    shared_int=read_data+1;
    sleep(2); // 让线程多运行几秒
    printf("****** End Thread:thread id=0x%x ******\n\n",pthread_self());
    My_pthread_spin_unlock(&spin_lock);// 解锁
    return read_data;
}

void test_spinlock()
{
    M_TRACE("---------  Begin test_spinlock()  ---------\n");
    //********** 初始化 *************//
    shared_int=0;
    My_pthread_spin_init(&spin_lock,PTHREAD_PROCESS_PRIVATE);
    //******** 创建子线程 *********//
    const int N=3;
    pthread_t threads[N];

    My_pthread_spin_lock(&spin_lock); // 加锁
    for(int i=0;i<N;i++)
        My_pthread_create(threads+i,NULL,thread_func,0);
    My_pthread_spin_unlock(&spin_lock); // 解锁
    //******** 等待子线程结束 *********//
    int values[N];
    for(int i=0;i<N;i++)
        thread_join_int(threads[i],values+i);

    My_pthread_spin_destroy(&spin_lock);
    M_TRACE("---------  End test_spinlock()  ---------\n\n");
}
