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
#include"rwlock_.h"
#include"../header.h"

int My_pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
{
    int result=pthread_rwlock_init(rwlock,attr);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_init(%p,%p) failed,because %s\n",
               pid,rwlock,attr,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_init(%p,%p) ok\n",
               pid,rwlock,attr);
    }
    return result;
}
int My_pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
    int result=pthread_rwlock_destroy(rwlock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_destroy(%p) failed,because %s\n",
               pid,rwlock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_destroy(%p) ok\n",
               pid,rwlock);
    }
    return result;
}
int My_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
    int result=pthread_rwlock_rdlock(rwlock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_rdlock(%p) failed,because %s\n",
               pid,rwlock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_rdlock(%p) ok\n",
               pid,rwlock);
    }
    return result;
}
int My_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
    int result=pthread_rwlock_wrlock(rwlock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_wrlock(%p) failed,because %s\n",
               pid,rwlock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_wrlock(%p) ok\n",
               pid,rwlock);
    }
    return result;
}
int My_pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
    int result=pthread_rwlock_unlock(rwlock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_unlock(%p) failed,because %s\n",
               pid,rwlock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_unlock(%p) ok\n",
               pid,rwlock);
    }
    return result;
}
int My_pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
    int result=pthread_rwlock_tryrdlock(rwlock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_tryrdlock(%p) failed,because %s\n",
               pid,rwlock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_tryrdlock(%p) ok\n",
               pid,rwlock);
    }
    return result;
}
int My_pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)
{
    int result=pthread_rwlock_trywrlock(rwlock);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_trywrlock(%p) failed,because %s\n",
               pid,rwlock,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_trywrlock(%p) ok\n",
               pid,rwlock);
    }
    return result;
}
int My_pthread_rwlock_timedrdlock(pthread_rwlock_t *rwlock,const struct timespect* tsptr)
{
    int result=pthread_rwlock_timedrdlock(rwlock,tsptr);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_timedrdlock(%p,%p) failed,because %s\n",
               pid,rwlock,tsptr,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_timedrdlock(%p,%p) ok\n",
               pid,rwlock,tsptr);
    }
    return result;
}
int My_pthread_rwlock_timedwrlock(pthread_rwlock_t *rwlock,const struct timespect* tsptr)
{
    int result=pthread_rwlock_timedwrlock(rwlock,tsptr);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_rwlock_timedwrlock(%p,%p) failed,because %s\n",
               pid,rwlock,tsptr,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_rwlock_timedwrlock(%p,%p) ok\n",
               pid,rwlock,tsptr);
    }
    return result;
}


extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);
extern struct timespec* rel_to_abs_time(int seconds);

/*!
 * \brief rwlock : 读写锁
 */
static pthread_rwlock_t rwlock;
/*!
 * \brief shared_int : 全局共享数据
 */
static int shared_int;

/*!
 * \brief thread_func : 线程的工作例程
 * \param arg : 参数，这里是个整数，如果 arg=0 则不加锁；如果 arg=1 则加读锁；如果arg=2 则加读锁；如果 arg=3 则 tryrdlock； 如果 arg=4 则 trywrlock； 如果 arg=5 则 timedrdlock ； 如果 arg=6 则 timedwrlock
 * \return :返回读到的 shared_int 值（如果加锁失败则返回 -1）
 */
static void* thread_func (void* arg)
{
    //********** 选择七种加锁行为 *************//
    switch ((int) arg) {
    case 0: //不加锁
        break;
    case 1: // 加读锁
        if(0!=My_pthread_rwlock_rdlock(&rwlock))
            return -1;// 加锁失败
        break;
    case 2: // 加写锁
        if(0!=My_pthread_rwlock_wrlock(&rwlock))
            return -1;// 加锁失败
        break;
    case 3: // tryrdlock；
        if(0!=My_pthread_rwlock_tryrdlock(&rwlock))
            return -1;// 加锁失败
        break;
    case 4: // trywrlock；
        if(0!=My_pthread_rwlock_trywrlock(&rwlock))
            return -1;// 加锁失败
        break;
    case 5: // timedrdlock
        if(0!=My_pthread_rwlock_timedrdlock(&rwlock,rel_to_abs_time(1)))
            return -1;// 加锁失败
        break;
    case 6: // timedwrlock
        if(0!=My_pthread_rwlock_timedwrlock(&rwlock,rel_to_abs_time(1)))
            return -1;// 加锁失败
        break;
    default:
        break;
    }

    printf("\n****** Begin Thread:thread id=0x%x ******\n",pthread_self());
    int read_data=shared_int;
    printf("read shared_int :%d.\n",read_data);
    shared_int=read_data+1;
    sleep(2); // 让线程多运行几秒
    printf("****** End Thread:thread id=0x%x ******\n\n",pthread_self());
    //********** 解锁 ****************//
    if(0!=(int)arg) // 曾经加锁，则解锁
        My_pthread_rwlock_unlock(&rwlock);
    return read_data;
}


void test_rwlock()
{
    M_TRACE("---------  Begin test_rwlock()  ---------\n");
    //********** 初始化 *************//
    shared_int=99;
    My_pthread_rwlock_init(&rwlock,NULL);
    //******** 创建子线程 *********//
    const int N=5;
    pthread_t threads[N];
    int rw_int[]={2,2,2,2,2}; // 每个线程的锁的类型
    for(int i=0;i<N;i++)
        My_pthread_create(threads+i,NULL,thread_func,rw_int[i]);
    //******** 等待子线程结束 *********//
    int values[N];
    for(int i=0;i<N;i++)
        thread_join_int(threads[i],values+i);

    My_pthread_rwlock_destroy(&rwlock);
    M_TRACE("---------  End test_rwlock()  ---------\n\n");
}
