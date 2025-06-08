#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define TEST_FILE_NAME "test_thread_ftruncate_write.log"
#define CHAR_LEN 1000
#define ONE_WRITE_LEN 100

static char CHAR_DATA_A[CHAR_LEN] = { 'a' };
static char CHAR_DATA_B[CHAR_LEN] = { 'b' };

static void *test_func(void *arg)
{
	int fd = -1;
	int all_write_len = 0;
	char *data = (char *)arg;
	sleep(1);

	fd = open(TEST_FILE_NAME, O_RDWR | O_CREAT, ALLPERMS);
	if (fd < 0) {
		perror("open error");
		return NULL;
	}

	if (ftruncate(fd, 0)) {
		perror("ftruncate error");
		return NULL;
	}

	while (all_write_len < CHAR_LEN) {
		if (write(fd, data, ONE_WRITE_LEN) != ONE_WRITE_LEN) {
			perror("write error");
			return NULL;
		}
		all_write_len += ONE_WRITE_LEN;
		sleep(1);
	}
	close(fd);
	return NULL;
}

int demo_test_thread_ftruncate_write_main(void)
{
	pthread_t tid1 = 0;
	pthread_t tid2 = 0;
	(void)CHAR_DATA_A;
	(void)CHAR_DATA_B;
	pthread_create(&tid1, NULL, test_func, CHAR_DATA_A);
	pthread_create(&tid2, NULL, test_func, CHAR_DATA_B);
	printf("pthread tid1=%lu; pthread tid1=%lu\n", tid1, tid2);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return EXIT_SUCCESS;
}
