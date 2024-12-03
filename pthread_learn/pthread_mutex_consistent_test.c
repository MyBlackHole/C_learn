#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SHM_NAME "pthread_mutex_consistent_test"

static pthread_mutex_t *mtx;
static int fd;

void shm_mutex_init(pthread_mutex_t **mutex)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	/* 设置: PTHREAD_MUTEX_ROBUST 来使得 mutex 可恢复一致性 */
	pthread_mutexattr_setrobust(&attr, PTHREAD_MUTEX_ROBUST);

	if ((fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0660)) == -1)
		perror("shm_open");

	if (ftruncate(fd, sizeof(pthread_mutex_t)) == -1)
		perror("ftruncate");

	if ((*mutex = mmap(NULL, sizeof(pthread_mutex_t),
			   PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) ==
	    MAP_FAILED)
		perror("mmap");

	pthread_mutex_init(*mutex, &attr);
}

int demo_pthread_mutex_consistent_main(int argc, char *argv[])
{
	int ret = EXIT_SUCCESS;
	pid_t pid;

	shm_mutex_init(&mtx);

	if ((pid = fork()) < 0) {
		perror("fork.");
	} else if (pid == 0) {
		// child
		sleep(1);
		printf("Setting lock...\n");
		pthread_mutex_lock(mtx);
		printf("Locked. Now exiting without unlocking.\n");
		exit(EXIT_SUCCESS);
	} else {
		int retry = 5;
		while (retry--) {
			ret = pthread_mutex_lock(mtx);

			if (ret == EOWNERDEAD) {
				printf("pthread_mutex_lock() returned EOWNERDEAD\n");

				printf("Now make the mutex consistent\n");
				ret = pthread_mutex_consistent(mtx);
				if (ret != 0) {
					perror("pthread_mutex_consistent");
					ret = EXIT_FAILURE;
					goto err_exit;
				}

				printf("Mutex is now consistent; unlocking\n");
				ret = pthread_mutex_unlock(mtx);
				if (ret != 0) {
					perror("pthread_mutex_unlock");
					ret = EXIT_FAILURE;
					goto err_exit;
				}

			} else if (ret < 0) {
				perror("pthread_mutex_lock unexpectedly failed");
				goto err_exit;
			} else {
				printf("pthread_mutex_lock success.\n");
				printf("do somthing.... \n");
				ret = pthread_mutex_unlock(mtx);
				if (ret != 0) {
					perror("pthread_mutex_unlock");
					ret = EXIT_FAILURE;
					goto err_exit;
				}
			}

			sleep(1);
		}
	}
err_exit:
	shm_unlink(SHM_NAME);
	exit(ret);
}

// output:
//
// ❯ xmake run pthread_learn pthread_mutex_consistent
// pthread_mutex_lock success.
// do somthing....
// pthread_mutex_lock success.
// do somthing....
// Setting lock...
// Locked. Now exiting without unlocking.
// pthread_mutex_lock() returned EOWNERDEAD
// Now make the mutex consistent
// Mutex is now consistent; unlocking
// pthread_mutex_lock success.
// do somthing....
// pthread_mutex_lock success.
// do somthing....
