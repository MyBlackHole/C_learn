#ifndef _CONFIG_H__
#define _CONFIG_H__

#include <sys/time.h>
#include <pthread.h>
#include "bandwidth.h"

#define USEC_PER_SEC 1000000

#define AIO_SPEEDD_INDEX 0
#define OSSUTIL 1
#define TEST1 2
#define TEST2 3
#define TEST3 4

#define MAX_CONFIG 10

struct config {
	int master;
	int bandwidth;
	int remaining_bandwidth;
	long current_time;
	long start_time;
};

typedef struct config config_t;

// long uclock();
// int cnofig_init(config_t *config);
// int config_update_bandwidth(config_t *config, int bandwidth);
// int config_get_dowload_speed(config_t *config);

struct configs {
	pthread_mutex_t mutex;
	pthread_mutexattr_t mutex_attr;
	pthread_cond_t update;
	pthread_condattr_t cond_attr;
	int total_bandwidth;
	int shmid;
	int config_num;
	int total_config;
	struct bwlimit bwlimits[MAX_CONFIG];
};

typedef struct configs configs_t;

configs_t *alloc_configs(int total_bandwidth);
configs_t *get_configs();
struct bwlimit *get_config(configs_t *configs, int index);
void put_config(configs_t *configs, int index);
void chmdt_configs(configs_t *configs);
void free_configs(configs_t *configs);

#endif /* _CONFIG_H__ */
