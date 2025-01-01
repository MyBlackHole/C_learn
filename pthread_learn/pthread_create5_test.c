#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COUNT 4000

static char *file_path = NULL;

static void *thread_func(void *arg)
{
	pthread_t self = pthread_self();
	char buffer[1024];
	int fd = 0;
	fd = open(file_path, O_RDONLY | O_DIRECT);
	if (fd < 0) {
		perror("open");
		pthread_exit((void *)EXIT_FAILURE);
	}

	for (;;) {
		int n = pread(fd, buffer, sizeof(buffer), 0);
		if (n < 0) {
			printf("Thread %ld: pread failed\n", (long)self);
			pthread_exit((void *)EXIT_FAILURE);
		}
		if (n == 0) {
			break;
		}
		if (n != sizeof(buffer)) {
			printf("Thread %ld: read %d bytes, expected %ld bytes\n",
			       (long)self, n, sizeof(buffer));
		}
		/*printf("Thread %ld: read %d bytes\n", self, n);*/
	}
	pthread_exit((void *)EXIT_SUCCESS);
}

int demo_create5_main(int argc, char **argv)
{
	pthread_t tid[COUNT] = { 0 };

	if (argc < 2) {
		printf("Usage: %s <file_path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	file_path = argv[1];

	for (int i = 0; i < COUNT; i++) {
		pthread_create(&tid[i], NULL, thread_func, NULL);
	}

	for (int i = 0; i < COUNT; i++) {
		pthread_join(tid[i], NULL);
	}
	return EXIT_SUCCESS;
}
