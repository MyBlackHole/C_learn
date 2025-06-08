/*
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

#include <time.h>

typedef int (*taskRunFunc)(void *arg1, void *arg2, void *arg3);

/* This structure represents a background Job. It is only used locally to this
 * file as the API deos not expose the internals at all.
 *
 * ��ʾ��̨��������ݽṹ
 *
 * ����ṹֻ�� API ʹ�ã����ᱻ��¶���ⲿ��
 */
struct bio_job {
	// ���񴴽�ʱ��ʱ��
	time_t time; /* Time at which the job was created. */

	/* Job specific arguments pointers. If we need to pass more than three
   * arguments we can just pass a pointer to a structure or alike.
   *
   * ����Ĳ�����������������ʱ�����Դ���������߽ṹ
   */
	void *arg1, *arg2, *arg3;

	taskRunFunc func;
};

/* Exported API */
void bioInit(void);
int bioCreateBackgroundJob(int type, void *arg1, void *arg2, void *arg3,
			   taskRunFunc func);
unsigned long long bioPendingJobsOfType(int type);
void bioWaitPendingJobsLE(int type, unsigned long long num);
// time_t bioOlderJobOfType(int type);
void bioKillThreads(void);
void *bioProcessBackgroundJobs(void *arg);

//����������ޣ����������ô�࣬˵�������ѹ������
#define BIO_MAX_PENDING_NUM 1000

/* Background job opcodes */
//�����������̳߳أ��ֱ�����ͬ������
#define BIO_TASK1 0 //����1��Ӧ���̳߳�
#define BIO_TASK2 1 //����2��Ӧ���̳߳�
#define BIO_NUM_OPS 2

#define BIO_TASK_THREAD_NUM 5 //ÿ���̳߳����߳���
