/* APUE code examples .
 * :copyright: (c) 2016 by the huaxz1986@163.com.
 * :license: lgpl-3.0, see LICENSE for more details.
 */

/*
 *   第十一章：线程
 *
 * 测试 pthread_mutex_t 相关函数的用法
 *
 */
#include"mutex_.h"
#include"../header.h"


int My_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
    int result=pthread_mutex_init(mutex,attr);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_mutex_init(%p,%p) failed,because %s\n",
               pid,mutex,attr,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_mutex_init(%p,%p) ok\n",
               pid,mutex,attr);
    }
    return result;
}
int My_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    int result=pthread_mutex_destroy(mutex);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_mutex_destroy(%p) failed,because %s\n",
               pid,mutex,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_mutex_destroy(%p) ok\n",
               pid,mutex);
    }
    return result;
}
int My_pthread_mutex_lock(pthread_mutex_t *mutex)
{
    int result=pthread_mutex_lock(mutex);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_mutex_lock(%p) failed,because %s\n",
               pid,mutex,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_mutex_lock(%p) ok\n",
               pid,mutex);
    }
    return result;
}
int My_pthread_mutex_trylock(pthread_mutex_t *mutex)
{
    int result=pthread_mutex_trylock(mutex);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_mutex_trylock(%p) failed,because %s\n",
               pid,mutex,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_mutex_trylock(%p) ok\n",
               pid,mutex);
    }
    return result;
}
int My_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    int result=pthread_mutex_unlock(mutex);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call pthread_mutex_unlock(%p) failed,because %s\n",
               pid,mutex,strerror(result));
    }else
    {
        printf("thread(0x%x) call pthread_mutex_unlock(%p) ok\n",
               pid,mutex);
    }
    return result;
}
int My_pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *tsptr)
{
    int result=pthread_mutex_timedlock(mutex,tsptr);
    pid_t pid=pthread_self();
    if(0!=result)
    {
        printf("thread(0x%x) call thread_mutex_timedlock(%p,%p) failed,because %s\n",
               pid,mutex,tsptr,strerror(result));
    }else
    {
        printf("thread(0x%x) call thread_mutex_timedlock(%p,%p) ok\n",
               pid,mutex,tsptr);
    }
    return result;
}

struct timespec* rel_to_abs_time(int seconds)
{
    static struct timespec tsp;
    int result=clock_gettime(CLOCK_REALTIME,&tsp);
    if(-1==result)
    {
        printf("rel_to_abs_time(%d) error,because %s\n",
               seconds,strerror(errno));
        return NULL;
    }
    tsp.tv_sec+=1; // 绝对时间为：当前时间加 1 秒
    return &tsp;
}

extern void thread_join_int(pthread_t tid, int *rval_pptr);
extern int My_pthread_create(pthread_t *tidp, const pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);

/*!
 * \brief mutex : 互斥量
 */
static pthread_mutex_t mutex;
/*!
 * \brief shared_int : 全局共享数据
 */
static int shared_int;

/*!
 * \brief thread_func : 线程的工作例程
 * \param arg : 参数，这里是个整数，如果 arg=0 则不加锁；如果 arg=1 则加锁；如果arg=2 则使用 try_lock，如果 arg=3, 则使用 timedlock
 * \return :返回读到的 shared_int 值（如果加锁失败则返回 -1）
 */
static void* thread_func (void* arg)
{
    //********** 选择四种加锁行为 *************//
    switch ((int)arg) {
    case 0: // 不加锁
        break;
    case 1:
        if(0!=My_pthread_mutex_lock(&mutex)) //加锁
            return -1;// 加锁失败
        break;
    case 2:
        if(0!=My_pthread_mutex_trylock(&mutex)) //trylock
            return -1;// 加锁失败
        break;
    case 3:
        if(0!=My_pthread_mutex_timedlock(&mutex,rel_to_abs_time(1))) //timedlock
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
        My_pthread_mutex_unlock(&mutex);
    return read_data;
}


void test_mutex()
{
    M_TRACE("---------  Begin test_mutex()  ---------\n");
    //********** 初始化 *************//
    shared_int=99;
    My_pthread_mutex_init(&mutex,NULL);
    //******** 创建子线程 *********//
    const int N=5;
    pthread_t threads[N];
    for(int i=0;i<N;i++)
        My_pthread_create(threads+i,NULL,thread_func,0);
    //******** 等待子线程结束 *********//
    int values[N];
    for(int i=0;i<N;i++)
        thread_join_int(threads[i],values+i);

    My_pthread_mutex_destroy(&mutex);
    M_TRACE("---------  End test_mutex()  ---------\n\n");
}
