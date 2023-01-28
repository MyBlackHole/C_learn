#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DATENUM 64

pthread_barrier_t barrier;
pthread_t pid;

char *get_time_str(char *date) {
  time_t t = time(NULL);
  struct tm tm;
  struct tm *tp = localtime_r(&t, &tm);
  strftime(date, DATENUM, "%Y-%m-%d %H:%M:%S", tp);
  return date;
}

void *initor(void *args) {
  char *data_time;
  data_time = malloc(sizeof(char) * DATENUM);

  printf("--- thread init work (%s) ---\n", get_time_str(data_time));

  // 模拟耗时运行
  sleep(10);
  pthread_barrier_wait(&barrier);

  printf("--- thread start work (%s) ---\n", get_time_str(data_time));
  // 模拟耗时运行
  sleep(10);

  printf("--- thread stop work (%s) ---\n", get_time_str(data_time));

  free(data_time);
  return NULL;
}

int main(int argc, char *argv[]) {
  char *data_time;
  data_time = malloc(sizeof(char) * DATENUM);

  pthread_barrier_init(&barrier, NULL, 2);
  printf("*** main thread barrier init done ***\n");
  pthread_create(&pid, NULL, &initor, NULL);

  printf("--- main waiting (%s) ---\n", get_time_str(data_time));

  pthread_barrier_wait(&barrier);
  pthread_barrier_destroy(&barrier);

  printf("--- main waiting (%s) ---\n", get_time_str(data_time));

  sleep(30);

  pthread_join(pid, NULL);

  printf("--- main waiting (%s) ---\n", get_time_str(data_time));

  free(data_time);
  exit(EXIT_SUCCESS);
}
