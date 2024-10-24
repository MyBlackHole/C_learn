#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>

union semun {
	int val; /* Value for SETVAL */
	struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
	unsigned short *array; /* Array for GETALL, SETALL */
	struct seminfo *__buf; /* Buffer for IPC_INFO
                                           (Linux-specific) */
};

void p(int semid, int num)
{
	struct sembuf sop;
	sop.sem_num = num;
	sop.sem_op = -1;
	sop.sem_flg = SEM_UNDO;
	semop(semid, &sop, 1);
}

void v(int semid, int num)
{
	struct sembuf sop;
	sop.sem_num = num;
	sop.sem_op = 1;
	sop.sem_flg = SEM_UNDO;
	semop(semid, &sop, 1);
}

int main()
{
	int semid;
	int shmid;
	char *shmaddr;
	key_t key1;
	key_t key2;
	key1 = ftok(".", 1);
	key2 = ftok(".", 2);
	shmid = shmget(key1, 1024, IPC_CREAT | 0666);
	semid = semget(key2, 2, IPC_CREAT | 0666);
	union semun set1;
	set1.val = 1;
	semctl(semid, 0, SETVAL, set1);
	/*union semun set2;*/
	/*set2.val = 0;*/

	p(semid, 1); //上第二把锁，代表写入完成可以读取
	shmaddr = shmat(shmid, 0, 0); //连接共享内存
	printf("contect:%s\n", shmaddr); //打印内容
	shmdt(shmaddr);
	v(semid, 0); //释放第一把锁，代表可以删除共享内存
	printf("read down!\n");
}
