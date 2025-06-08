#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

// 配置参数
#define LOG_BUFFER_SIZE 1024 * 1024 * 4 // 每个缓冲区容量
#define LOG_MAX_MSG_SIZE 1024 * 4 // 单条日志最大长度
#define LOG_MAX_FILE_SIZE (100 * 1024 * 1024) // 100MB
#define LOG_MAX_FILES 5 // 最大保留日志文件数

typedef enum {
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_ERROR
} LogLevel;

typedef struct {
	char message[LOG_MAX_MSG_SIZE];
	time_t timestamp;
	const char *filename;
	int line;
	LogLevel level;
} LogEntry;

typedef struct {
	LogEntry buffer[2][LOG_BUFFER_SIZE]; // 双缓冲
	volatile int active_buffer; // 当前活动缓冲区索引
	volatile size_t buffer_count; // 当前缓冲条目数
	volatile int flush_flag; // 刷新标志

	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pthread_t thread;
	int running;

	char base_filename[256];
	int current_fd;
	size_t current_size;
	int max_files;
} Logger;

static Logger logger;

static void *log_worker(void *arg);
static void rotate_logs();

// 初始化日志系统
int log_init(const char *filename, LogLevel level)
{
	memset(&logger, 0, sizeof(Logger));
	logger.active_buffer = 0;
	logger.buffer_count = 0;
	logger.flush_flag = 0;
	logger.running = 1;
	logger.max_files = LOG_MAX_FILES;

	strncpy(logger.base_filename, filename,
		sizeof(logger.base_filename) - 1);

	// 打开初始日志文件
	logger.current_fd =
		open(logger.base_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (logger.current_fd == -1) {
		fprintf(stderr, "Failed to open log file: %s\n",
			strerror(errno));
		return -1;
	}

	pthread_mutex_init(&logger.mutex, NULL);
	pthread_cond_init(&logger.cond, NULL);
	pthread_create(&logger.thread, NULL, log_worker, NULL);
	return 0;
}

// 日志工作线程
static void *log_worker(void *arg)
{
	LogEntry flush_buffer[LOG_BUFFER_SIZE * 2];
	size_t flush_count = 0;

	while (1) {
		pthread_mutex_lock(&logger.mutex);

		// 等待数据或停止信号
		while (!logger.flush_flag && logger.running) {
			pthread_cond_wait(&logger.cond, &logger.mutex);
		}

		if (!logger.running && !logger.flush_flag)
			break;

		// 交换缓冲区
		size_t entries_to_flush = logger.buffer_count;

		// 复制数据到临时缓冲区
		memcpy(flush_buffer + flush_count,
		       logger.buffer[logger.active_buffer],
		       entries_to_flush * sizeof(LogEntry));
		flush_count += entries_to_flush;

		logger.active_buffer = 1 - logger.active_buffer;
		logger.buffer_count = 0;
		logger.flush_flag = 0;

		pthread_mutex_unlock(&logger.mutex);

		// 写入文件
		for (size_t i = 0; i < flush_count; i++) {
			struct tm tm_info;
			char time_buf[64];
			const LogEntry *entry = &flush_buffer[i];

			localtime_r(&entry->timestamp, &tm_info);
			strftime(time_buf, sizeof(time_buf),
				 "%Y-%m-%d %H:%M:%S", &tm_info);

			const char *level_str = "";
			switch (entry->level) {
			case LOG_LEVEL_DEBUG:
				level_str = "DEBUG";
				break;
			case LOG_LEVEL_INFO:
				level_str = "INFO";
				break;
			case LOG_LEVEL_WARNING:
				level_str = "WARN";
				break;
			case LOG_LEVEL_ERROR:
				level_str = "ERROR";
				break;
			}

			char log_line[LOG_MAX_MSG_SIZE + 256];
			int len = snprintf(log_line, sizeof(log_line),
					   "[%s][%s][%s:%d] %s\n", time_buf,
					   level_str, entry->filename,
					   entry->line, entry->message);

			ssize_t written =
				write(logger.current_fd, log_line, len);
			if (written > 0) {
				logger.current_size += written;
			}

			// 检查文件大小
			if (logger.current_size >= LOG_MAX_FILE_SIZE) {
				rotate_logs();
			}
		}
		flush_count = 0;
	}

	close(logger.current_fd);
	return NULL;
}

// 日志轮转
static void rotate_logs()
{
	close(logger.current_fd);

	// 重命名旧日志文件
	for (int i = logger.max_files - 1; i > 0; i--) {
		char old_name[4096], new_name[4096];
		sprintf(old_name, "%s.%d", logger.base_filename, i);
		sprintf(new_name, "%s.%d", logger.base_filename, i + 1);
		rename(old_name, new_name);
	}

	// 移动当前日志
	rename(logger.base_filename, strcat(logger.base_filename, ".1"));

	// 创建新日志文件
	logger.current_fd =
		open(logger.base_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	logger.current_size = 0;
}

// 记录日志
void log_write(LogLevel level, const char *filename, int line, const char *fmt,
	       ...)
{
	va_list args;
	va_start(args, fmt);

	char message[LOG_MAX_MSG_SIZE];
	vsnprintf(message, sizeof(message), fmt, args);

	va_end(args);

	pthread_mutex_lock(&logger.mutex);

	if (logger.buffer_count < LOG_BUFFER_SIZE) {
		LogEntry *entry = &logger.buffer[logger.active_buffer]
						[logger.buffer_count++];
		entry->timestamp = time(NULL);
		entry->level = level;
		entry->filename = filename;
		entry->line = line;
		strncpy(entry->message, message, sizeof(entry->message));

		// 触发刷新条件
		if (logger.buffer_count >= LOG_BUFFER_SIZE * 0.8) {
			logger.flush_flag = 1;
			pthread_cond_signal(&logger.cond);
		}
	} else {
		// 应急处理：直接写入stderr
		struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		fprintf(stderr, "[EMERG][%ld.%09ld] BUFFER FULL: %s\n",
			ts.tv_sec, ts.tv_nsec, message);
	}

	pthread_mutex_unlock(&logger.mutex);
}

// 关闭日志系统
void log_shutdown()
{
	pthread_mutex_lock(&logger.mutex);
	logger.running = 0;
	logger.flush_flag = 1;
	pthread_cond_signal(&logger.cond);
	pthread_mutex_unlock(&logger.mutex);

	pthread_join(logger.thread, NULL);
	pthread_mutex_destroy(&logger.mutex);
	pthread_cond_destroy(&logger.cond);
}

// 使用宏简化调用
#define LOG_DEBUG(...) \
	log_write(LOG_LEVEL_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_write(LOG_LEVEL_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) \
	log_write(LOG_LEVEL_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) \
	log_write(LOG_LEVEL_ERROR, __FILE__, __LINE__, __VA_ARGS__)

static void *test_thread(void *arg);

// 示例程序
int demo_log_test_main()
{
	if (log_init("app.log", LOG_LEVEL_INFO) != 0) {
		return 1;
	}

	// 多线程测试
	pthread_t threads[4];
	for (int i = 0; i < 4; i++) {
		pthread_create(&threads[i], NULL, test_thread,
			       (void *)(intptr_t)i);
	}

	for (int i = 0; i < 4; i++) {
		pthread_join(threads[i], NULL);
	}

	log_shutdown();
	return 0;
}

static void *test_thread(void *arg)
{
	int id = (int)(intptr_t)arg;
	for (int i = 0; i < 1000; i++) {
		LOG_INFO("[Thread %d] Count %d", id, i);
	}
	return NULL;
}
