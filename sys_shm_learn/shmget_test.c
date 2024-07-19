// shm_test.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>

#define BUFFERSIZE 1024
int main(int argc, char const *argv[])
{
	int shmid;
	char *shmadd;
	// 创建一个共享内存对象
	if ((shmid = shmget(IPC_PRIVATE, BUFFERSIZE, 0666)) < 0) {
		perror("shmget error");
		exit(-1);
	} else {
		printf("create shared memory:%d\n", shmid);
	}
	system("ipcs -m");
	// 挂载共享内存到进程中
	if ((shmadd = shmat(shmid, 0, 0)) < (char *)0) {
		perror("shmat error");
		exit(-1);
	} else {
		printf("attached shared memory\n");
	}
	system("ipcs -m");
	// 卸载共享内存
	if (shmdt(shmadd) < 0) {
		perror("shmdt error");
		exit(-1);
	} else {
		printf("deleted shared memory\n");
	}
	system("ipcs -m");
	// 完成对共享内存的控制,释放共享内存
	//  IPC_RMID：删除这片共享内存
	if (shmctl(shmid, IPC_RMID, 0) < 0) {
		perror("shmctl error");
		exit(-1);
	}
	printf("release shared memory\n");
	exit(0);

	return 0;
}
