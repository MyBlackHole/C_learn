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
typedef struct ipcnode {
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;
	pthread_cond_t read, write;
	pthread_condattr_t cond_attr;
	char buf[64];
	int buflen;
	int stat; //状态：1表示read工作，-1表示read结束工作。
} ipcnode;
int main()
{
	//挂载共享内存
	key_t fk = ftok("./test.txt", 9);
	int shid = shmget(fk, 512, IPC_EXCL | 0666);
	if (shid < 0) {
		perror("shmget");
		exit(1);
	}
	ipcnode *node = shmat(shid, NULL, 0);
	node->stat = 1; //通知read端开始工作
	while (1) {
		//锁逻辑：读写只能同时拥有一个mutex锁
		//若共享内存中buf没有数据则等待read端传递write的信号
		//一次写工作完成后传递read信号并归还mutex锁
		pthread_mutex_lock(&node->mutex);
		if (node->buflen == 0)
			pthread_cond_wait(&node->write, &node->mutex);
		//如果读端主动关闭程序，跳出循环,进行善后工作
		if (node->stat == -1)
			break;
		write(1, node->buf, node->buflen);
		node->buflen = 0;
		pthread_cond_signal(&node->read);
		pthread_mutex_unlock(&node->mutex);
	}
	//结束善后工作
	//销毁锁和删除共享内存
	pthread_mutex_destroy(&node->mutex);
	pthread_cond_destroy(&node->read);
	pthread_cond_destroy(&node->write);
	pthread_condattr_destroy(&node->cond_attr);
	shmctl(shid, IPC_RMID, 0);
	return 0;
}
