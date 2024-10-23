#ifndef _CONFIG_H__
#define _CONFIG_H__

#include <sys/time.h>

#define AIO_SPEEDD_INDEX 0
#define OSSUTIL 1
#define TEST1 2
#define TEST2 3

struct config {
	int master;
	int bandwidth;
	int remaining_bandwidth;
	time_t current_time;
};

typedef struct config config_t;

struct configs {
	int total_bandwidth;
	int shmid;
	struct config config[10];
};

typedef struct configs configs_t;

configs_t *alloc_configs(int total_bandwidth);
void free_configs(configs_t *configs);

#endif /* _CONFIG_H__ */
