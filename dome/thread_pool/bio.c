/* Background I/O service for Redis.
 *
 * Redis �ĺ�̨ I/O ����
 *
 * This file implements operations that we need to perform in the background.
 *
 * bio ʵ���˽��������ں�ִ̨�еĹ��ܡ�
 *
 * Currently there is only a single operation, that is a background close(2)
 * system call. This is needed as when the process is the last owner of a
 * reference to a file closing it means unlinking it, and the deletion of the
 * file is slow, blocking the server.
 *
 * Ŀǰ�ں�ִ̨�е�ֻ�� close(2) ������
 * ��Ϊ����������ĳ���ļ������һ��ӵ����ʱ��
 * �ر�һ���ļ����� unlinking ����
 * ����ɾ���ļ��ǳ�����������ϵͳ��
 * �������ǽ� close(2) �ŵ���̨���С�
 *
 * (��ע�����ڲ�ֹ close(2) ���� AOF �ļ��� fsync Ҳ�Ƿŵ���ִ̨�еģ�
 *
 * In the future we'll either continue implementing new things we need or
 * we'll switch to libeio. However there are probably long term uses for this
 * file as we may want to put here Redis specific background tasks (for instance
 * it is not impossible that we'll need a non blocking FLUSHDB/FLUSHALL
 * implementation).
 *
 * �����̨���������ܻ����Ӹ��๦�ܣ������л��� libeio ����ȥ��
 * �������ǿ��᳤ܻ��ʹ������ļ����Ա�֧��һЩ Redis �����еĺ�̨������
 * ����˵���������ǿ�����Ҫһ���������� FLUSHDB ���� FLUSHALL Ҳ˵������
 *
 * DESIGN
 * ------
 *
 * The design is trivial, we have a structure representing a job to perform
 * and a different thread and job queue for every job type.
 * Every thread wait for new jobs in its queue, and process every job
 * sequentially.
 *
 * ��ƺܼ򵥣�
 * ��һ���ṹ��ʾҪִ�еĹ�������ÿ�����͵Ĺ�����һ�����к��̣߳�
 * ÿ���̶߳�˳���ִ�ж����еĹ�����
 *
 * Jobs of the same type are guaranteed to be processed from the least
 * recently inserted to the most recently inserted (older jobs processed
 * first).
 *
 * ͬһ���͵Ĺ����� FIFO ��˳��ִ�С�
 *
 * Currently there is no way for the creator of the job to be notified about
 * the completion of the operation, this will only be added when/if needed.
 *
 * Ŀǰ��û�а취���������ʱִ֪ͨ���ߣ�������Ҫ��ʱ�򣬻�ʵ��������ܡ�
 *
 * ----------------------------------------------------------------------------
 *
 * Copyright (c) 2009-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

//#include "redis.h"
#include "bio.h"
#include "adlist.h"
#include "zmalloc.h"
#include <string.h>

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

// �����̣߳��⻥����������  BIO_NUM_OPSΪ�̳߳����飬ÿ���߳�
// ��BIO_TASK_THREAD_NUM���̣߳��ֱ�����ͬ������
static pthread_t bio_threads[BIO_NUM_OPS][BIO_TASK_THREAD_NUM];
static pthread_mutex_t bio_mutex[BIO_NUM_OPS];
static pthread_cond_t bio_condvar[BIO_NUM_OPS];

// ��Ź����Ķ���
static list *bio_jobs[BIO_NUM_OPS];

/* The following array is used to hold the number of pending jobs for every
 * OP type. This allows us to export the bioPendingJobsOfType() API that is
 * useful when the main thread wants to perform some operation that may involve
 * objects shared with the background thread. The main thread will just wait
 * that there are no longer jobs of this type to be executed before performing
 * the sensible operation. This data is also useful for reporting. */
// ��¼ÿ������ job �������ж��� job �ȴ�ִ��
static unsigned long long bio_pending[BIO_NUM_OPS];

void *bioProcessBackgroundJobs(void *arg);

/* Make sure we have enough stack to perform all the things we do in the
 * main thread.
 *
 * ���߳�ջ��С
 */
#define THREAD_STACK_SIZE (1024 * 1024 * 4)

/* Initialize the background system, spawning the thread.
 *
 * ��ʼ����̨����ϵͳ�������߳�
 */
void bioInit(void) {
  pthread_attr_t attr;
  pthread_t thread;
  size_t stacksize;
  int j;

  /* Initialization of state vars and objects
   *
   * ��ʼ�� job ���У��Լ��߳�״̬
   */
  for (j = 0; j < BIO_NUM_OPS; j++) {
    pthread_mutex_init(&bio_mutex[j], NULL);
    pthread_cond_init(&bio_condvar[j], NULL);
    bio_jobs[j] = listCreate();
    bio_pending[j] = 0;
  }

  /* Set the stack size as by default it may be small in some system
   *
   * ����ջ��С
   */
  pthread_attr_init(&attr);
  pthread_attr_getstacksize(&attr, &stacksize);
  if (!stacksize)
    stacksize = 1; /* The world is full of Solaris Fixes */
  while (stacksize < THREAD_STACK_SIZE)
    stacksize *= 2;
  pthread_attr_setstacksize(&attr, stacksize);

  /* Ready to spawn our threads. We use the single argument the thread
   * function accepts in order to pass the job ID the thread is
   * responsible of.
   *
   * �����߳�
   */
  for (j = 0; j < BIO_NUM_OPS; j++) {
    void *arg = (void *)(unsigned long)j;

    int i = 0;
    for (i = 0; i < BIO_TASK_THREAD_NUM; i++) {
      if (pthread_create(&thread, &attr, bioProcessBackgroundJobs, arg) != 0) {
        printf("Fatal: Can't initialize Background Jobs.");
        exit(1);
      }
      bio_threads[j][i] = thread;
    }
  }
}

/*
 * ������̨����
 */ //���µ��߳�bio_threads��ִ��job   bioProcessBackgroundJobs��ִ��
int bioCreateBackgroundJob(int type, void *arg1, void *arg2, void *arg3,
                           taskRunFunc func) {
  struct bio_job *job = zmalloc(sizeof(*job));

  job->time = time(NULL);
  job->arg1 = arg1;
  job->arg2 = arg2;
  job->arg3 = arg3;
  // bioProcessBackgroundJobs��ִ��
  job->func = func;

  pthread_mutex_lock(&bio_mutex[type]);
  bio_pending[type]++;
  if (bio_pending[type] >= BIO_MAX_PENDING_NUM) {
    pthread_mutex_unlock(&bio_mutex[type]);
    printf("task type:%d have much overstock, over %d\r\n", type,
           BIO_MAX_PENDING_NUM);
    return -1; //�����ѹ����
  }

  // ���¹����������
  listAddNodeTail(bio_jobs[type], job);

  // ����
  pthread_cond_signal(&bio_condvar[type]);

  pthread_mutex_unlock(&bio_mutex[type]);

  return 0;
}

/*
 * �̻߳ص�������������̨����  ִ�ж����е�����
 */
void *bioProcessBackgroundJobs(void *arg) {
  struct bio_job *job;
  unsigned long type = (unsigned long)arg;
  sigset_t sigset;

  /* Make the thread killable at any time, so that bioKillThreads()
   * can work reliably. */
  /*
   * ʹ�߳���ʱ������ֹ
   */
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

  // ����
  pthread_mutex_lock(&bio_mutex[type]);
  /* Block SIGALRM so we are sure that only the main thread will
   * receive the watchdog signal. */
  // sigemptyset(&sigset);
  // sigaddset(&sigset, SIGALRM);
  // if (pthread_sigmask(SIG_BLOCK, &sigset, NULL))
  //     printf("Warning: can't mask SIGALRM in bio.c thread: %s",
  //     strerror(errno));

  while (1) {
    listNode *ln;

    /* The loop always starts with the lock hold. */
    if (listLength(bio_jobs[type]) == 0) {
      // ���ߵȴ�������ʱ����
      pthread_cond_wait(&bio_condvar[type], &bio_mutex[type]);
      continue;
    }

    /* Pop the job from the queue.
     *
     * ȡ��������ɾ���������е��׸�����
     */
    ln = listFirst(bio_jobs[type]);
    job = ln->value;

    // ��ִ����ɵ�����Ӷ�����ɾ�������������������
    listDelNode(bio_jobs[type], ln);
    bio_pending[type]--;

    /* It is now possible to unlock the background system as we know have
     * a stand alone job structure to process.*/
    pthread_mutex_unlock(&bio_mutex[type]);

    /* Process the job accordingly to its type. */
    // ִ������
    if (type == BIO_TASK1) {
      job->func(job->arg1, job->arg1, job->arg3);

    } else if (type == BIO_TASK2) {
      job->func(job->arg1, job->arg1, job->arg3);

    } else {
      printf("Wrong job type in bioProcessBackgroundJobs(). type:%ld\r\n",
             type);
    }

    // printf("job:%p , type:%d\r\n", job, type);
    zfree(job);

    /* Lock again before reiterating the loop, if there are no longer
     * jobs to process we'll block again in pthread_cond_wait(). */
    pthread_mutex_lock(&bio_mutex[type]);

    // listDelNode(bio_jobs[type],ln);
    // bio_pending[type]--;
  }
}

/* Return the number of pending jobs of the specified type.
 *
 * ���صȴ��е� type ���͵Ĺ���������
 */
unsigned long long bioPendingJobsOfType(int type) {
  unsigned long long val;

  pthread_mutex_lock(&bio_mutex[type]);
  val = bio_pending[type];
  pthread_mutex_unlock(&bio_mutex[type]);

  return val;
}

/* Kill the running bio threads in an unclean way. This function should be
 * used only when it's critical to stop the threads for some reason.
 *
 * ������������ֱ��ɱ�����̣�ֻ�ڳ������ش���ʱʹ��
 *
 * Currently Redis does this only on crash (for instance on SIGSEGV) in order
 * to perform a fast memory check without other threads messing with memory.
 */
void bioKillThreads(void) {
  int err, j, i;

  for (j = 0; j < BIO_NUM_OPS; j++) {
    for (i = 0; i < BIO_TASK_THREAD_NUM; j++) {
      if (pthread_cancel(bio_threads[j][i]) == 0) {
        if ((err = pthread_join(bio_threads[j][i], NULL)) != 0) {
          printf("Bio thread for job type #%d can be joined: %s", j,
                 strerror(err));
        } else {
          printf("Bio thread for job type #%d terminated", j);
        }
      }
    }
  }
}