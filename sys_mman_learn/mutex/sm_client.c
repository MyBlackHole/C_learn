#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <pthread.h>

#include "sm_common.h"
#include <unistd.h>

int main(void)
{
	int shm_id = -1;
	int ret = -1;
	/*int key = -1;*/
	int running = 1;
	struct sm_msg *msg = NULL;
	void *shared_memory = NULL;

	// 创建一片共享内存，使用同一个key: SM_ID
	/*key = ftok(".", 1);*/
	/*printf("key: %d\n", key);*/
	shm_id = shmget((key_t)SM_ID, sizeof(struct sm_msg), 0666 | IPC_CREAT);
	if (shm_id < 0) {
		perror("fail to shmget");
		exit(1);
	}

	shared_memory = shmat(shm_id, NULL, 0);
	if (shared_memory == NULL) {
		perror("Failed to shmat");
		exit(1);
	}

	msg = (struct sm_msg *)shared_memory;

	/*char buf[32];*/
	while (running) {
		printf("wait lock\n");
		pthread_mutex_lock(&msg->sm_mutex); // 阻塞等待内部的互斥锁
		printf("get lock\n");
		sleep(5);
		pthread_mutex_unlock(&msg->sm_mutex);
		printf("release lock\n");
		sleep(2);
	}

	ret = shmdt(shared_memory);
	if (ret < 0) {
		perror("Failed to shmdt");
		exit(1);
	}

#if 0 //Do this in server.
	if(shmctl(shm_id, IPC_RMID, 0) < 0)
	{
		perror("failed to shmctl");
		exit(1);
	}
#endif
	return 0;
}
