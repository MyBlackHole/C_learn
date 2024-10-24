#include "config.h"
#include "config.h"
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

static configs_t *p_configs = NULL;

static void sig_handler(int sig)
{
	if (p_configs != NULL) {
		free_configs(p_configs);
	}
	printf("signal %d received, exit...\n", sig);
	exit(sig);
}

int main(int argc, char *argv[])
{
	struct bwlimit *p_bw = NULL;
	int total_bandwidth = 0;
	int loop_interval = 1;
	int average_bandwidth = 0;

	if (argc != 2) {
		printf("usage: ./client <total_bandwidth>\n");
		return EXIT_FAILURE;
	}

	total_bandwidth = atoi(argv[1]);

	p_configs = alloc_configs(total_bandwidth);
	if (p_configs == NULL) {
		printf("alloc_configs error\n");
		return EXIT_FAILURE;
	}

	// 信号处理函数
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGKILL, sig_handler);

	for (int i = 0; i < p_configs->total_config; i++) {
		p_bw = &p_configs->bwlimits[i];
		bandwidth_limit_init(p_bw, 0, COPY_BUFLEN);
	}

	while (true) {
		if (p_configs->total_bandwidth <= 0) {
			printf("total bandwidth is 0, sleep %d\n",
			       loop_interval);
			sleep(loop_interval);
			continue;
		}
		average_bandwidth = 0;
		if (p_configs->config_num == 0) {
			printf("config_num is 0, sleep %d\n", loop_interval);
			sleep(loop_interval);
			continue;
		}

		average_bandwidth =
			p_configs->total_bandwidth / p_configs->config_num;
		for (int i = 0; i < p_configs->total_config; i++) {
			p_bw = &p_configs->bwlimits[i];
			if (p_bw->state) {
				bandwidth_reset_limit(p_bw, average_bandwidth);
			}
		}

		printf("online clients: %d\n", p_configs->config_num);
		sleep(loop_interval);
	}
	free_configs(p_configs);
	return EXIT_SUCCESS;
}
