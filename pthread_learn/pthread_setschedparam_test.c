/* pthreads_sched_test.c */
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error_en(en, msg)    \
	do {                        \
		errno = en;         \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0)

static void usage(char *prog_name, char *msg)
{
	if (msg != NULL) {
		fputs(msg, stderr);
	}

	fprintf(stderr, "Usage: %s [options]\n", prog_name);
	fprintf(stderr, "Options are:\n");
#define fpe(msg) fprintf(stderr, "\t%s", msg) /* Shorter */
	fpe("-a<policy><prio> Set scheduling policy and priority in\n");
	fpe("                 thread attributes object\n");
	fpe("                 <policy> can be\n");
	fpe("                     f  SCHED_FIFO\n");
	fpe("                     r  SCHED_RR\n");
	fpe("                     o  SCHED_OTHER\n");
	fpe("-A               Use default thread attributes object\n");
	fpe("-i {e|i}         Set inherit scheduler attribute to\n");
	fpe("                 'explicit' or 'inherit'\n");
	fpe("-m<policy><prio> Set scheduling policy and priority on\n");
	fpe("                 main thread before pthread_create() call\n");
	exit(EXIT_FAILURE);
}

static int get_policy(char policy_type, int *policy)
{
	switch (policy_type) {
	case 'f':
		*policy = SCHED_FIFO;
		return 1;
	case 'r':
		*policy = SCHED_RR;
		return 1;
	case 'o':
		*policy = SCHED_OTHER;
		return 1;
	default:
		return 0;
	}
}

static void display_sched_attr(int policy, struct sched_param *param)
{
	printf("    policy=%s, priority=%d\n",
	       (policy == SCHED_FIFO)  ? "SCHED_FIFO" :
	       (policy == SCHED_RR)    ? "SCHED_RR" :
	       (policy == SCHED_OTHER) ? "SCHED_OTHER" :
					 "???",
	       param->sched_priority);
}

static void display_thread_sched_attr(char *msg)
{
	int policy;
	int ret;
	struct sched_param param;

	ret = pthread_getschedparam(pthread_self(), &policy, &param);
	if (ret != 0) {
		handle_error_en(ret, "pthread_getschedparam");
	}

	printf("%s\n", msg);
	display_sched_attr(policy, &param);
}

static void *thread_start(void *arg)
{
	display_thread_sched_attr("Scheduler attributes of new thread");

	return NULL;
}

int demo_pthread_setschedparam_main(int argc, char *argv[])
{
	int ret;
	int opt;
	int inheritsched;
	int use_null_attrib;
	int policy;
	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_t *attrp;
	char *attr_sched_str;
	char *main_sched_str;
	char *inheritsched_str;
	struct sched_param param;

	/* Process command-line options. */
	use_null_attrib = 0;
	attr_sched_str = NULL;
	main_sched_str = NULL;
	inheritsched_str = NULL;

	while ((opt = getopt(argc, argv, "a:Ai:m:")) != -1) {
		switch (opt) {
		case 'a':
			attr_sched_str = optarg;
			break;
		case 'A':
			use_null_attrib = 1;
			break;
		case 'i':
			inheritsched_str = optarg;
			break;
		case 'm':
			main_sched_str = optarg;
			break;
		default:
			usage(argv[0], "Unrecognized option\n");
		}
	}

	if (use_null_attrib &&
	    (inheritsched_str != NULL || attr_sched_str != NULL)) {
		usage(argv[0], "Can't specify -A with -i or -a\n");
	}

	/* Optionally set scheduling attributes of main thread,
       and display the attributes. */
	if (main_sched_str != NULL) {
		if (!get_policy(main_sched_str[0], &policy)) {
			usage(argv[0], "Bad policy for main thread (-m)\n");
		}
		param.sched_priority = strtol(&main_sched_str[1], NULL, 0);

		// 设置调度配置
		ret = pthread_setschedparam(pthread_self(), policy, &param);
		if (ret != 0) {
			handle_error_en(ret, "pthread_setschedparam");
		}
	}

	// 展示线程调度属性
	display_thread_sched_attr("Scheduler settings of main thread");
	printf("\n");

	/* Initialize thread attributes object according to options. */
	attrp = NULL;

	if (!use_null_attrib) {
		// 属性初始化
		ret = pthread_attr_init(&attr);
		if (ret != 0) {
			handle_error_en(ret, "pthread_attr_init");
		}
		attrp = &attr;
	}

	if (inheritsched_str != NULL) {
		if (inheritsched_str[0] == 'e') {
			inheritsched = PTHREAD_EXPLICIT_SCHED;
		} else if (inheritsched_str[0] == 'i') {
			inheritsched = PTHREAD_INHERIT_SCHED;
		} else {
			usage(argv[0], "Value for -i must be 'e' or 'i'\n");
		}

		// 设置继承的线程调度属性
		ret = pthread_attr_setinheritsched(&attr, inheritsched);
		if (ret != 0) {
			handle_error_en(ret, "pthread_attr_setinheritsched");
		}
	}

	if (attr_sched_str != NULL) {
		if (!get_policy(attr_sched_str[0], &policy)) {
			usage(argv[0], "Bad policy for 'attr' (-a)\n");
		}
		param.sched_priority = strtol(&attr_sched_str[1], NULL, 0);

		// 设置线程策略
		ret = pthread_attr_setschedpolicy(&attr, policy);
		if (ret != 0) {
			handle_error_en(ret, "pthread_attr_setschedpolicy");
		}
		// 设置策略属性
		ret = pthread_attr_setschedparam(&attr, &param);
		if (ret != 0) {
			handle_error_en(ret, "pthread_attr_setschedparam");
		}
	}

	/* If we initialized a thread attributes object, display
       the scheduling attributes that were set in the object. */
	if (attrp != NULL) {
		// 获取策略属性
		ret = pthread_attr_getschedparam(&attr, &param);
		if (ret != 0) {
			handle_error_en(ret, "pthread_attr_getschedparam");
		}
		// 获取策略类型
		ret = pthread_attr_getschedpolicy(&attr, &policy);
		if (ret != 0) {
			handle_error_en(ret, "pthread_attr_getschedpolicy");
		}

		printf("Scheduler settings in 'attr'\n");
		display_sched_attr(policy, &param);

		pthread_attr_getinheritsched(&attr, &inheritsched);
		printf("    inheritsched is %s\n",
		       (inheritsched == PTHREAD_INHERIT_SCHED)	? "INHERIT" :
		       (inheritsched == PTHREAD_EXPLICIT_SCHED) ? "EXPLICIT" :
								  "???");
		printf("\n");
	}

	/* Create a thread that will display its scheduling attributes. */
	// 创建线程
	ret = pthread_create(&thread, attrp, &thread_start, NULL);
	if (ret != 0) {
		handle_error_en(ret, "pthread_create");
	}

	/* Destroy unneeded thread attributes object. */
	if (!use_null_attrib) {
		// 销魂线程属性对象
		ret = pthread_attr_destroy(&attr);
		if (ret != 0) {
			handle_error_en(ret, "pthread_attr_destroy");
		}
	}

	// 等待线程退出
	ret = pthread_join(thread, NULL);
	if (ret != 0) {
		handle_error_en(ret, "pthread_join");
	}

	exit(EXIT_SUCCESS);
}
