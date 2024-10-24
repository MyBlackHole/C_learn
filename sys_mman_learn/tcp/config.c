#include "config.h"
#include "comm.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

long uclock()
{
	struct timeval tv = { 0 };
	if (gettimeofday(&tv, NULL))
		return -1;
	return ((long)tv.tv_sec * USEC_PER_SEC + tv.tv_usec);
}

int cnofig_init(config_t *config)
{
	memset(config, 0, sizeof(config_t));
	config->bandwidth = 0;
	config->remaining_bandwidth = 0;
	config->current_time = uclock();
	return 0;
}

int config_update_bandwidth(config_t *config, int bandwidth)
{
	__sync_fetch_and_add(&config->remaining_bandwidth, bandwidth);
	return 0;
}

int config_reset_bandwidth(config_t *config)
{
	long time_diff = 0;
	long now = uclock();

	time_diff = now - config->current_time;
	if (time_diff > 0) {
		printf("time_diff %ld\n", time_diff);
		usleep(time_diff);
	}

	config->remaining_bandwidth = 0;
	config->current_time = now;
	return 0;
}

int config_get_dowload_speed(config_t *config)
{
	int ret = 0;
	long now = 0;

	if (config->bandwidth > 0) {
		while (true) {
			if (config->bandwidth > config->remaining_bandwidth) {
				now = uclock();
				config->current_time = now;
				ret = true;
				break;
			} else {
				config_reset_bandwidth(config);
			}
		}
	} else {
		ret = true;
	}
	return ret;
}

configs_t *alloc_configs(int total_bandwidth)
{
	int ret = 0;
	int shmid = CreateShm(sizeof(configs_t));
	if (shmid < 0) {
		printf("CreateShm failed\n");
		return NULL;
	}

	configs_t *p_configs = shmat(shmid, NULL, 0);
	if (p_configs == NULL) {
		printf("shmat failed\n");
		return NULL;
	}
	memset(p_configs, 0, sizeof(configs_t));
	p_configs->total_bandwidth = total_bandwidth;
	p_configs->shmid = shmid;
	p_configs->total_config = MAX_CONFIG;

	ret = pthread_mutexattr_init(&p_configs->mutex_attr);
	if (ret < 0) {
		printf("pthread_mutexattr_init failed");
		return NULL;
	}
	ret = pthread_mutexattr_setpshared(&p_configs->mutex_attr,
					   PTHREAD_PROCESS_SHARED);
	if (ret < 0) {
		printf("pthread_mutexattr_setpshared failed");
		return NULL;
	}
	ret = pthread_condattr_init(&p_configs->cond_attr);
	if (ret < 0) {
		printf("pthread_condattr_init failed");
		return NULL;
	}
	ret = pthread_condattr_setpshared(&p_configs->cond_attr,
					  PTHREAD_PROCESS_SHARED);
	if (ret < 0) {
		printf("pthread_condattr_setpshared failed");
	}
	ret = pthread_mutex_init(&p_configs->mutex, &p_configs->mutex_attr);
	if (ret < 0) {
		printf("pthread_mutex_init failed");
		return NULL;
	}
	ret = pthread_cond_init(&p_configs->update, &p_configs->cond_attr);
	if (ret < 0) {
		printf("pthread_cond_init failed");
		return NULL;
	}
	return p_configs;
}

configs_t *get_configs()
{
	int shmid = GetShm(sizeof(configs_t));
	if (shmid < 0) {
		printf("GetShm failed\n");
		return NULL;
	}
	configs_t *p_configs = shmat(shmid, NULL, 0);
	if (p_configs == NULL) {
		printf("shmat failed\n");
		return NULL;
	}
	return p_configs;
}

void chmdt_configs(configs_t *configs)
{
	shmdt(configs);
}

config_t *get_config(configs_t *configs, int index)
{
	if (index < 0 || index >= configs->total_config) {
		printf("Invalid index %d\n", index);
		return NULL;
	}
	return &configs->configs[index];
}

void free_configs(configs_t *configs)
{
	pthread_cond_destroy(&configs->update);
	pthread_condattr_destroy(&configs->cond_attr);
	pthread_mutex_destroy(&configs->mutex);
	pthread_mutexattr_destroy(&configs->mutex_attr);
	DestroyShm(configs->shmid);
	shmdt(configs);
}
