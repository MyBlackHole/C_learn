#include "config.h"
#include "comm.h"
#include <string.h>

configs_t *alloc_configs(int total_bandwidth)
{
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
	return p_configs;
}

void free_configs(configs_t *configs)
{
	DestroyShm(configs->shmid);
	shmdt(configs);
}
