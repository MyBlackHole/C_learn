#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

static sem_t sem_one;
static sem_t sem_two;
static int num;

void *read(void *arg)
{
	int index;
	for (index = 0; index < 5; index++) {
		fputs("Input num: ", stdout);

		sem_wait(&sem_two);
		scanf("%d", &num);
		sem_post(&sem_one);
	}
	return NULL;
}

void *accu(void *arg)
{
	int sum = 0, index;
	for (index = 0; index < 5; index++) {
		sem_wait(&sem_one);
		sum += num;
		sem_post(&sem_two);
	}
	printf("Result: %d \n", sum);
	return NULL;
}

int demo_sem_destroy_main(int argc, char const *argv[])
{
	pthread_t id_t1, id_t2;
	sem_init(&sem_one, 0, 0);
	sem_init(&sem_two, 0, 1);

	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return EXIT_SUCCESS;
}
