#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

// 使用宏初始化互斥锁与条件变量
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int i = 1;

void *thread1(void *junk) {
  for (i = 1; i <= 9; i++) {
    printf("IN one\n");
    pthread_mutex_lock(&mutex); //
    if (i % 3 == 0)
      pthread_cond_signal(&cond); /*条件改变，发送信号，通知t_b进程*/
    else
      printf("thead1:%d\n", i);
    pthread_mutex_unlock(&mutex); //*解锁互斥量*/
    printf("Up Mutex\n");
    sleep(10);
  }
  pthread_exit(NULL);
}

void *thread2(void *junk) {
  while (i < 9) {
    printf("IN two \n");
    pthread_mutex_lock(&mutex);
    if (i % 3 != 0)
      pthread_cond_wait(&cond, &mutex); /*等待*/
    printf("thread2:%d\n", i);
    pthread_mutex_unlock(&mutex);
    printf("Down Mutex\n");
    sleep(10);
  }
  pthread_exit(NULL);
}

int main(void) {
  pthread_t t_a;
  pthread_t t_b;

  // 使用init方法初始化条件变量与互斥量
  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mutex, NULL);

  pthread_create(&t_a, NULL, thread1, (void *)NULL); /*创建线程t_a*/
  pthread_create(&t_b, NULL, thread2, (void *)NULL); /*创建线程t_b*/
  pthread_join(t_b, NULL);                           /*等待线程t_b结束*/
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
  exit(0);
}
