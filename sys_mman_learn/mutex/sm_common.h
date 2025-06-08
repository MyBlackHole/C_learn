#ifndef __SM_COMMON_H__
#define __SM_COMMON_H__

#include <pthread.h>

#define SM_BUF_SIZE 1024
#define SM_ID 0x1122

// 定义的共享内存区数据结构
// 内部携带一把互斥锁
struct sm_msg {
	int flag;
	pthread_mutex_t sm_mutex; // 定义互斥锁
	char buf[SM_BUF_SIZE];
};

#endif
