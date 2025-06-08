#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h> // glibc队列宏

#define TASK_TYPE_DATA 0
#define TASK_TYPE_END 1

/************** 任务结构定义 **************/
typedef struct download_task {
	int type;
	char url[256];
	char data[1024];
	STAILQ_ENTRY(download_task) entries; // glibc队列链接字段
} download_task_t;

typedef struct parse_task {
	int type;
	char content[1024];
	STAILQ_ENTRY(parse_task) entries; // glibc队列链接字段
} parse_task_t;

/************** 线程安全队列封装 **************/
typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	STAILQ_HEAD(download_stailq_head, download_task) head; // FIFO队列头
} download_queue_t;

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	STAILQ_HEAD(parse_stailq_head, parse_task) head; // FIFO队列头
} parse_queue_t;

/************** 初始化队列 **************/
void init_download_queue(download_queue_t *q)
{
	pthread_mutex_init(&q->mutex, NULL);
	pthread_cond_init(&q->cond, NULL);
	STAILQ_INIT(&q->head);
}

void init_parse_queue(parse_queue_t *q)
{
	pthread_mutex_init(&q->mutex, NULL);
	pthread_cond_init(&q->cond, NULL);
	STAILQ_INIT(&q->head);
}

/************** 下载队列操作 **************/

void enqueue_download(download_queue_t *q, download_task_t *task)
{
	pthread_mutex_lock(&q->mutex);
	STAILQ_INSERT_TAIL(&q->head, task, entries); // 插入队尾保证FIFO
	pthread_cond_signal(&q->cond);
	pthread_mutex_unlock(&q->mutex);
}

download_task_t *dequeue_download(download_queue_t *q)
{
	pthread_mutex_lock(&q->mutex);
	while (STAILQ_EMPTY(&q->head)) {
		pthread_cond_wait(&q->cond, &q->mutex); // 阻塞等待条件变量
	}
	download_task_t *task = STAILQ_FIRST(&q->head);
	STAILQ_REMOVE_HEAD(&q->head, entries); // 从队头移除保证FIFO
	pthread_mutex_unlock(&q->mutex);
	return task;
}

/************** 解析队列操作 **************/
void enqueue_parse(parse_queue_t *q, parse_task_t *task)
{
	pthread_mutex_lock(&q->mutex);
	STAILQ_INSERT_TAIL(&q->head, task, entries); // 插入队尾
	pthread_cond_signal(&q->cond);
	pthread_mutex_unlock(&q->mutex);
}

parse_task_t *dequeue_parse(parse_queue_t *q)
{
	pthread_mutex_lock(&q->mutex);
	while (STAILQ_EMPTY(&q->head)) {
		pthread_cond_wait(&q->cond, &q->mutex);
	}
	parse_task_t *task = STAILQ_FIRST(&q->head);
	STAILQ_REMOVE_HEAD(&q->head, entries); // 从队头移除
	pthread_mutex_unlock(&q->mutex);
	return task;
}

/************** 线程参数结构 **************/
typedef struct {
	download_queue_t *download_queue;
	parse_queue_t *parse_queue;
} thread_args_t;

/************** Meta线程 **************/
void *meta_thread(void *arg)
{
	download_queue_t *queue = (download_queue_t *)arg;

	// 生成3个下载任务（按顺序1→2→3）
	for (int i = 1; i <= 3; i++) {
		download_task_t *task = malloc(sizeof(download_task_t));
		task->type = TASK_TYPE_DATA;
		snprintf(task->url, sizeof(task->url),
			 "http://example.com/file%d", i);
		enqueue_download(queue, task);
		printf("[Meta] 生成任务: %s\n", task->url);
	}

	// 发送结束标记（确保是最后一个任务）
	download_task_t *end_task = malloc(sizeof(download_task_t));
	end_task->type = TASK_TYPE_END;
	enqueue_download(queue, end_task);
	return NULL;
}

/************** 下载线程 **************/
void *download_thread(void *arg)
{
	thread_args_t *args = (thread_args_t *)arg;

	while (1) {
		// 从下载队列头部取出任务（FIFO）
		download_task_t *task = dequeue_download(args->download_queue);

		if (task->type == TASK_TYPE_END) {
			// 传递结束标记到解析队列
			parse_task_t *end_task = malloc(sizeof(parse_task_t));
			end_task->type = TASK_TYPE_END;
			enqueue_parse(args->parse_queue, end_task);
			free(task);
			printf("[下载] 收到结束信号，退出\n");
			break;
		}

		// 模拟下载过程（保持顺序）
		snprintf(task->data, sizeof(task->data), "下载数据: %s",
			 task->url);
		printf("[下载] 处理: %s\n", task->url);

		// 生成解析任务（保持相同顺序）
		parse_task_t *parse_task = malloc(sizeof(parse_task_t));
		parse_task->type = TASK_TYPE_DATA;
		strncpy(parse_task->content, task->data,
			sizeof(parse_task->content));
		enqueue_parse(args->parse_queue, parse_task);

		free(task); // 释放下载任务内存
	}
	return NULL;
}

/************** 解析线程 **************/
void *parse_thread(void *arg)
{
	parse_queue_t *queue = (parse_queue_t *)arg;

	while (1) {
		// 从解析队列头部取出任务（FIFO）
		parse_task_t *task = dequeue_parse(queue);

		if (task->type == TASK_TYPE_END) {
			free(task);
			printf("[解析] 收到结束信号，退出\n");
			break;
		}

		printf("[解析] 处理: %s\n", task->content);
		free(task); // 释放解析任务内存
	}
	return NULL;
}

/************** 主函数 **************/
int demo_STAILQ_INIT_main()
{
	download_queue_t download_queue;
	parse_queue_t parse_queue;
	init_download_queue(&download_queue);
	init_parse_queue(&parse_queue);

	pthread_t tid[3];
	thread_args_t args = { &download_queue,
			       &parse_queue }; // 统一传递双队列

	pthread_create(&tid[0], NULL, meta_thread, &download_queue);
	pthread_create(&tid[1], NULL, download_thread, &args); // 传递参数结构
	pthread_create(&tid[2], NULL, parse_thread, &parse_queue);

	// 等待所有线程结束
	for (int i = 0; i < 3; i++) {
		pthread_join(tid[i], NULL);
	}

	// 清理残留任务（保险机制）
	while (!STAILQ_EMPTY(&download_queue.head)) {
		download_task_t *task = STAILQ_FIRST(&download_queue.head);
		STAILQ_REMOVE_HEAD(&download_queue.head, entries);
		free(task);
	}
	while (!STAILQ_EMPTY(&parse_queue.head)) {
		parse_task_t *task = STAILQ_FIRST(&parse_queue.head);
		STAILQ_REMOVE_HEAD(&parse_queue.head, entries);
		free(task);
	}

	return EXIT_SUCCESS;
}
