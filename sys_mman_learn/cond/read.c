#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void myperror(char *s)
{
	perror(s);
	exit(1);
}
typedef struct ipcnode {
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;
	pthread_cond_t read, write;
	pthread_condattr_t cond_attr;
	char buf[64];
	int buflen;
	int stat; //状态：0表示等待write，1表示write开始工作，-1表示read/write结束工作。
} ipcnode;
int main()
{
	int retlen;
	char buf[64];
	key_t fk = ftok("./test.txt", 9);
	int shid = shmget(fk, 512, IPC_CREAT | 0666);
	ipcnode *node = shmat(shid, NULL, 0);
	//初始化互斥锁、条件变量、状态变量
	if (pthread_mutexattr_init(&node->mutex_attr) < 0)
		myperror("mutexattr_init");
	if (pthread_mutexattr_setpshared(&node->mutex_attr,
					 PTHREAD_PROCESS_SHARED) < 0)
		myperror("mutexattr_setshared");
	if (pthread_condattr_init(&node->cond_attr) < 0)
		myperror("mutexattr_init");
	if (pthread_condattr_setpshared(&node->cond_attr,
					PTHREAD_PROCESS_SHARED) < 0)
		myperror("mutexattr_setshared");
	if (pthread_mutex_init(&node->mutex, &node->mutex_attr) < 0)
		myperror("mutex_init");
	if (pthread_cond_init(&node->read, &node->cond_attr) < 0)
		myperror("read_init");
	if (pthread_cond_init(&node->write, &node->cond_attr) < 0)
		myperror("write_init");
	pthread_condattr_destroy(&node->cond_attr);
	node->buflen = 0;
	node->stat = 0;

	//等待write进程启动
	while (node->stat == 0) {
		printf("waiting for write process.\n");
		sleep(3);
	}

	printf("start working.\n");

	//开始循环写入
	while ((retlen = read(0, buf, 64)) > 0) {
		//锁逻辑：读写只能同时拥有一个mutex锁
		//若共享内存中buf有数据则等待write端传递read的信号
		//一次写工作完成后传递read信号并归还mutex锁
		if (!strncmp(buf, "-1", 2) || node->stat == -1)
			break;
		pthread_mutex_lock(&node->mutex);
		if (node->buflen > 0)
			pthread_cond_wait(&node->read, &node->mutex);
		strncpy(node->buf, buf, retlen);
		node->buflen = retlen;
		pthread_cond_signal(&node->write);
		pthread_mutex_unlock(&node->mutex);
	}

	//结束工作，通知write处理后续工作
	printf("exiting.\n");
	node->stat = -1;
	pthread_mutex_unlock(&node->mutex);
	pthread_cond_signal(&node->write);
	return 0;
}
