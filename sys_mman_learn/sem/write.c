#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// 创建或获取一个信号量组：若成功返回信号量集ID，失败返回-1
//int semget(key_t key, int num_sems, int sem_flags);
// 对信号量组进行操作，改变信号量的值：成功返回0，失败返回-1
//int semop(int semid, struct sembuf semoparray[], size_t numops);
// 控制信号量的相关信息
//int semctl(int semid, int sem_num, int cmd, ...);

// unsigned short sem_num;  /* semaphore number */
//           short          sem_op;   /* semaphore operation */
//           short          sem_flg;  /* operation flags */

// 创建或获取一个共享内存：成功返回共享内存ID，失败返回-1
//int shmget(key_t key, size_t size, int flag);
// 连接共享内存到当前进程的地址空间：成功返回指向共享内存的指针，失败返回-1
//void *shmat(int shm_id, const void *addr, int flag);
// 断开与共享内存的连接：成功返回0，失败返回-1
//int shmdt(void *addr);
// 控制共享内存的相关信息：成功返回0，失败返回-1
//int shmctl(int shm_id, int cmd, struct shmid_ds *buf);
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
	semop(semid, &sop, 1); //上锁操作
}

void v(int semid, int num)
{
	struct sembuf sop;
	sop.sem_num = num;
	sop.sem_op = 1;
	sop.sem_flg = SEM_UNDO;
	semop(semid, &sop, 1); //放锁操作
}

int main()
{
	int semid;
	int shmid;
	char *shmaddr; //用于shmat返回返回共享内存空间
	key_t key1;
	key_t key2; //创建key值
	key1 = ftok(".", 1);
	key2 = ftok(".", 2); //建立Key值
	shmid = shmget(key1, 1024, IPC_CREAT | 0666); //创建共享内存
	semid = semget(key2, 2, IPC_CREAT | 0666); //创建信号量
	union semun set1;
	set1.val = 1; //第一个信号量锁数量为1
	semctl(semid, 0, SETVAL, set1);
	/*union semun set2;*/
	/*set2.val = 0; //第二个信号量锁数量为0*/

	p(semid, 0); //对第一个信号上锁，只允许写入操作
	shmaddr = shmat(shmid, 0, 0); //进程连接共享内存
	strcpy(shmaddr, "you are a handsome boy"); //将内容写入共享内存
	shmdt(shmaddr); //断开共享内存
	v(semid, 1); //对第二个信号释放，目的是能让读入端进程读取内容

	p(semid, 0); //当读入端完成后，会上第一把锁，能消除信号量和共享内存
	shmctl(shmid, IPC_RMID, 0);
	semctl(semid, 0, IPC_RMID);
	semctl(semid, 1, IPC_RMID); //一系列删除操作
	printf("write down!\n");
}
