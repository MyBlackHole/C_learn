#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <seccomp.h>
#include <linux/capability.h>
#include <signal.h>
#include <errno.h>
#include <jansson.h>
#include <pthread.h>
#include <sys/resource.h>

#define PLUGIN_DIR "./plugins"
#define MAX_PLUGINS 32
#define SHM_SIZE 4096

// 插件状态枚举
typedef enum {
	PLUGIN_UNLOADED,
	PLUGIN_LOADED,
	PLUGIN_INITIALIZING,
	PLUGIN_RUNNING,
	PLUGIN_ERROR,
	PLUGIN_TERMINATED
} PluginState;

// 插件接口定义
typedef struct {
	const char *name;
	const char *version;
	int (*init)(void);
	int (*process)(const char *input, char **output);
	void (*cleanup)(void);
} PluginInterface;

// 安全插件上下文
typedef struct {
	void *dl_handle; // 动态库句柄
	PluginInterface *api; // 插件API指针
	pid_t sandbox_pid; // 沙箱进程PID
	int shm_fd; // 共享内存文件描述符
	void *shm_ptr; // 共享内存映射指针
	PluginState state; // 插件状态
	char path[PATH_MAX]; // 插件路径
	char error_msg[256]; // 错误信息
	time_t last_heartbeat; // 最后心跳时间
	pthread_t watchdog_thread; // 看门狗线程
} SecurePluginContext;

// 全局插件列表
SecurePluginContext plugins[MAX_PLUGINS];
int plugin_count = 0;
pthread_mutex_t plugins_mutex = PTHREAD_MUTEX_INITIALIZER;

// 设置资源限制
void set_resource_limits()
{
	// 设置内存限制为16MB
	struct rlimit mem_limit = { 16 * 1024 * 1024, 16 * 1024 * 1024 };
	setrlimit(RLIMIT_AS, &mem_limit);

	// 设置CPU时间限制为5秒
	struct rlimit cpu_limit = { 5, 5 };
	setrlimit(RLIMIT_CPU, &cpu_limit);

	// 设置文件大小限制为1MB
	struct rlimit file_limit = { 1024 * 1024, 1024 * 1024 };
	setrlimit(RLIMIT_FSIZE, &file_limit);

	// 设置文件描述符数量限制为8
	struct rlimit fd_limit = { 8, 8 };
	setrlimit(RLIMIT_NOFILE, &fd_limit);

	// 禁止生成core文件
	struct rlimit core_limit = { 0, 0 };
	setrlimit(RLIMIT_CORE, &core_limit);
}

// 设置seccomp过滤器
void set_seccomp_filter()
{
	scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
	if (!ctx)
		return;

	// 允许基本的系统调用
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(close), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(fstat), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(mmap), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(munmap), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(brk), 0);

	// 加载过滤器
	seccomp_load(ctx);
	seccomp_release(ctx);
}

// 在沙箱中运行插件
void run_plugin_in_sandbox(SecurePluginContext *context, const char *input)
{
	char *error;
	// // 设置资源限制
	// set_resource_limits();

	// // 设置seccomp过滤器
	// set_seccomp_filter();

	// 加载插件
	void *dl = dlopen(context->path, RTLD_LAZY);
	if (!dl) {
		fprintf(stderr, "Error loading plugin: %s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	// 获取插件API
	PluginInterface *(*get_plugin_api)(void) = dlsym(dl, "get_plugin_api");
	if (!get_plugin_api) {
		fprintf(stderr,
			"Error: Plugin does not export get_plugin_api\n");
		exit(EXIT_FAILURE);
	}

	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}

	PluginInterface *api = get_plugin_api();
	if (!api) {
		fprintf(stderr, "Error: get_plugin_api returned NULL\n");
		exit(EXIT_FAILURE);
	}

	// 初始化插件
	if (api->init() != 0) {
		fprintf(stderr, "Plugin initialization failed [%s]\n", dlerror());
		exit(EXIT_FAILURE);
	}

	// 处理数据
	char *output = NULL;
	int result = api->process(input, &output);

	// 将结果写入共享内存
	if (output) {
		size_t len = strlen(output);
		if (len > SHM_SIZE - 1) {
			len = SHM_SIZE - 1;
		}
		memcpy(context->shm_ptr, output, len);
		((char *)context->shm_ptr)[len] = '\0';
		free(output);
	} else {
		((char *)context->shm_ptr)[0] = '\0';
	}

	// 清理插件
	api->cleanup();
	dlclose(dl);

	exit(result);
}

// 插件看门狗线程
void *plugin_watchdog(void *arg)
{
	SecurePluginContext *context = (SecurePluginContext *)arg;

	while (context->state == PLUGIN_RUNNING) {
		sleep(1);

		// 检查心跳
		time_t current_time = time(NULL);
		if (current_time - context->last_heartbeat > 5) {
			fprintf(stderr,
				"Plugin %s watchdog timeout, terminating...\n",
				context->api->name);

			// 终止沙箱进程
			if (context->sandbox_pid > 0) {
				kill(context->sandbox_pid, SIGKILL);
			}

			// 更新状态
			context->state = PLUGIN_TERMINATED;
			strncpy(context->error_msg, "Watchdog timeout",
				sizeof(context->error_msg));
			break;
		}
	}

	return NULL;
}

// 安全加载插件
int secure_load_plugin(const char *path)
{
	if (plugin_count >= MAX_PLUGINS) {
		fprintf(stderr, "Maximum number of plugins reached\n");
		return -1;
	}

	// 创建共享内存
	char shm_name[32];
	snprintf(shm_name, sizeof(shm_name), "/plugin_shm_%d", plugin_count);
	int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0600);
	if (shm_fd == -1) {
		perror("shm_open");
		return -1;
	}

	if (ftruncate(shm_fd, SHM_SIZE) == -1) {
		perror("ftruncate");
		close(shm_fd);
		return -1;
	}

	void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,
			     shm_fd, 0);
	if (shm_ptr == MAP_FAILED) {
		perror("mmap");
		close(shm_fd);
		return -1;
	}

	// 初始化插件上下文
	SecurePluginContext *context = &plugins[plugin_count];
	memset(context, 0, sizeof(SecurePluginContext));
	strncpy(context->path, path, sizeof(context->path) - 1);
	context->shm_fd = shm_fd;
	context->shm_ptr = shm_ptr;
	context->state = PLUGIN_INITIALIZING;

	// 创建沙箱进程
	pid_t pid = fork();
	// pid_t pid = 0;
	if (pid == -1) {
		perror("fork");
		munmap(shm_ptr, SHM_SIZE);
		close(shm_fd);
		return -1;
	}

	if (pid == 0) {
		// 子进程运行插件
		run_plugin_in_sandbox(context, "initialize");
	} else {
		sleep(3);
		// 父进程
		context->sandbox_pid = pid;

		// 等待子进程初始化完成
		int status;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			// 初始化成功，加载API
			void *dl = dlopen(path, RTLD_LAZY);
			if (!dl) {
				fprintf(stderr,
					"Error loading plugin in parent: %s\n",
					dlerror());
				context->state = PLUGIN_ERROR;
				strncpy(context->error_msg, dlerror(),
					sizeof(context->error_msg));
			} else {
				PluginInterface *(*get_plugin_api)(void) =
					dlsym(dl, "get_plugin_api");
				if (!get_plugin_api) {
					fprintf(stderr,
						"Error: Plugin does not export get_plugin_api\n");
					context->state = PLUGIN_ERROR;
					strncpy(context->error_msg,
						"Missing get_plugin_api",
						sizeof(context->error_msg));
				} else {
					context->api = get_plugin_api();
					context->dl_handle = dl;
					context->state = PLUGIN_LOADED;
					context->last_heartbeat = time(NULL);

					// 启动看门狗线程
					pthread_create(
						&context->watchdog_thread, NULL,
						plugin_watchdog, context);

					printf("Plugin %s loaded securely\n",
					       context->api->name);
					plugin_count++;
					return 0;
				}
			}
		} else {
			fprintf(stderr, "Plugin initialization failed\n");
			context->state = PLUGIN_ERROR;
			strncpy(context->error_msg, "Initialization failed",
				sizeof(context->error_msg));
		}

		// 清理资源
		munmap(shm_ptr, SHM_SIZE);
		close(shm_fd);
	}

	return -1;
}

// 安全执行插件
int secure_execute_plugin(SecurePluginContext *context, const char *input,
			  char **output)
{
	if (context->state != PLUGIN_LOADED &&
	    context->state != PLUGIN_RUNNING) {
		fprintf(stderr, "Plugin not in executable state\n");
		return -1;
	}

	context->state = PLUGIN_RUNNING;
	context->last_heartbeat = time(NULL);

	// 创建新的沙箱进程执行插件
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	}

	if (pid == 0) {
		// 子进程运行插件
		run_plugin_in_sandbox(context, input);
	} else {
		// 父进程
		context->sandbox_pid = pid;

		int status;
		waitpid(pid, &status, 0);

		if (WIFEXITED(status)) {
			int exit_code = WEXITSTATUS(status);
			if (exit_code == 0) {
				// 执行成功，从共享内存读取结果
				*output = strdup(context->shm_ptr);
				context->state = PLUGIN_LOADED;
				context->last_heartbeat = time(NULL);
				return 0;
			} else {
				fprintf(stderr,
					"Plugin execution failed with code %d\n",
					exit_code);
				context->state = PLUGIN_ERROR;
				snprintf(context->error_msg,
					 sizeof(context->error_msg),
					 "Execution failed with code %d",
					 exit_code);
				return -1;
			}
		} else {
			fprintf(stderr,
				"Plugin execution terminated abnormally\n");
			context->state = PLUGIN_TERMINATED;
			strncpy(context->error_msg, "Abnormal termination",
				sizeof(context->error_msg));
			return -1;
		}
	}

	return -1;
}

// 安全卸载插件
void secure_unload_plugin(SecurePluginContext *context)
{
	if (context->state == PLUGIN_UNLOADED)
		return;

	// 终止看门狗线程
	if (context->watchdog_thread) {
		pthread_cancel(context->watchdog_thread);
		pthread_join(context->watchdog_thread, NULL);
	}

	// 终止沙箱进程
	if (context->sandbox_pid > 0) {
		kill(context->sandbox_pid, SIGTERM);
		waitpid(context->sandbox_pid, NULL, 0);
	}

	// 关闭动态库
	if (context->dl_handle) {
		dlclose(context->dl_handle);
	}

	// 清理共享内存
	if (context->shm_ptr) {
		munmap(context->shm_ptr, SHM_SIZE);
	}

	if (context->shm_fd > 0) {
		close(context->shm_fd);

		// 删除共享内存对象
		char shm_name[32];
		snprintf(shm_name, sizeof(shm_name), "/plugin_shm_%ld",
			 (long)(context - plugins));
		shm_unlink(shm_name);
	}

	// 重置状态
	memset(context, 0, sizeof(SecurePluginContext));
	context->state = PLUGIN_UNLOADED;
}

// 验证插件签名
int verify_plugin_signature(const char *path)
{
	// 这里应该实现实际的签名验证逻辑
	// 使用公钥验证插件的数字签名
	// 返回0表示验证成功，非0表示失败

	// 示例：检查文件权限
	struct stat st;
	if (stat(path, &st)) {
		perror("stat");
		return -1;
	}

	// 检查文件权限：不应有写权限
	if (st.st_mode & (S_IWGRP | S_IWOTH)) {
		fprintf(stderr, "Insecure file permissions: %s\n", path);
		return -1;
	}

	// 检查文件所有者
	if (st.st_uid != getuid()) {
		fprintf(stderr, "Plugin not owned by current user\n");
		return -1;
	}

	return 0;
}

// 加载所有安全插件
int load_secure_plugins(const char *path)
{
	// 验证插件签名
	if (verify_plugin_signature(path) != 0) {
		fprintf(stderr, "Signature verification failed for: %s\n",
			path);
		return -1;
	}

	// 安全加载插件
	if (secure_load_plugin(path) == 0) {
		printf("Successfully loaded plugin: %s\n", path);
		return 0;
	} else {
		fprintf(stderr, "Failed to load plugin: %s\n", path);
		return -1;
	}
}

// 插件心跳处理
void plugin_heartbeat(SecurePluginContext *context)
{
	if (context->state == PLUGIN_RUNNING) {
		context->last_heartbeat = time(NULL);
	}
}

// 恢复崩溃的插件
void recover_crashed_plugin(SecurePluginContext *context)
{
	printf("Attempting to recover plugin: %s\n", context->api->name);

	// 保存错误信息
	char error_msg[256];
	strncpy(error_msg, context->error_msg, sizeof(error_msg));

	// 卸载插件
	secure_unload_plugin(context);

	// 重新加载插件
	if (secure_load_plugin(context->path) == 0) {
		printf("Plugin %s recovered successfully\n",
		       context->api->name);
	} else {
		fprintf(stderr, "Failed to recover plugin %s: %s\n",
			context->api->name, error_msg);
	}
}

// 主程序
int main(int argc, char **argv)
{
	char plugin_input[256] = "black";

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <plugin path>\n", argv[0]);
		return EXIT_FAILURE;
	}

	// 加载所有安全插件
	load_secure_plugins(argv[1]);

	// 解析插件选择

	SecurePluginContext *context = &plugins[0];
	if (context->state != PLUGIN_LOADED) {
		printf("Plugin not ready\n");
		return EXIT_FAILURE;
	}

	// 执行插件
	char *output = NULL;
	int result = secure_execute_plugin(context, plugin_input, &output);

	if (result == 0) {
		printf("Plugin output: %s\n", output);
		free(output);
	} else {
		printf("Plugin execution failed: %s\n", context->error_msg);

		// 尝试恢复崩溃的插件
		if (context->state == PLUGIN_ERROR ||
		    context->state == PLUGIN_TERMINATED) {
			recover_crashed_plugin(context);
		}
	}

	// 发送心跳
	plugin_heartbeat(context);

	// 清理所有插件
	for (int i = 0; i < plugin_count; i++) {
		secure_unload_plugin(&plugins[i]);
	}

	return 0;
}

// 编译命令：
// ❯ xmake run demo_plugin_mange /run/media/black/Data/Documents/c/build/linux/x86_64/debug/libplugin_mange_plugin_1.so
// My Plugin Initialized
// My Plugin Cleaned Up
// Plugin MyPlugin loaded securely
// Successfully loaded plugin: /run/media/black/Data/Documents/c/build/linux/x86_64/debug/libplugin_mange_plugin_1.so
// My Plugin Initialized
// My Plugin Cleaned Up
// Plugin output: Processed: black
