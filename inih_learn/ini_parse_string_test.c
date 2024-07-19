/* Example: parse a simple configuration file */
/*
 * git@github.com:benhoyt/inih.git
 * inih 安装
 * ./vcpkg install inih
 */

#include <argp.h>
#include <ini.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
	const char *job_type;
	const char *backup_type;
	const char *instance;
	const char *xbsa_config;
} xbsa_env;

static int xbsa_env_handler(void *user, const char *section, const char *name,
			    const char *value)
{
	xbsa_env *xbsa_env_ref = (xbsa_env *)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("", "XBSACONFIG")) {
		xbsa_env_ref->xbsa_config = strdup(value);
	} else if (MATCH("", "INSTANCE")) {
		xbsa_env_ref->instance = strdup(value);
	} else if (MATCH("", "BACKUPTYPE")) {
		xbsa_env_ref->backup_type = strdup(value);
	} else if (MATCH("", "JOBTYPE")) {
		xbsa_env_ref->job_type = strdup(value);
	} else {
		return 0; /* unknown section/name, error */
	}
	return 1;
}

void free_xbsa_env(xbsa_env *xbsa_env_ref)
{
	if (xbsa_env_ref == 0) {
		return;
	}
	if (xbsa_env_ref->backup_type != 0) {
		free((void *)xbsa_env_ref->backup_type);
	}
	if (xbsa_env_ref->job_type != 0) {
		free((void *)xbsa_env_ref->job_type);
	}
	if (xbsa_env_ref->instance != 0) {
		free((void *)xbsa_env_ref->instance);
	}
	if (xbsa_env_ref->xbsa_config != 0) {
		free((void *)xbsa_env_ref->xbsa_config);
	}
}

bool is_file(char *fname);

int demo_ini_parse_string_main(int argc, char *argv[])
{
	char *envs[5];
	envs[0] = "JOBTYPE=backup";
	envs[1] = "BACKUPTYPE=";
	envs[2] = "INSTANCE=dn_6001_6002_6003";
	// envs[3] = "XBSACONFIG=/opt/xbsa/conf/xbsa_gaussdb_restore.conf";
	envs[3] = "XBSACONFIG1=/opt/xbsa/conf/xbsa_gaussdb_restore.conf";
	envs[4] = 0;
	xbsa_env xbsa_env = { 0 };

	for (int index = 0; envs[index] != 0; index++) {
		if (ini_parse_string(envs[index], xbsa_env_handler, &xbsa_env) <
		    0) {
			printf("ini_parse_string() failed for %s\n",
			       envs[index]);
			return EXIT_FAILURE;
		}
	}

	if (xbsa_env.xbsa_config != 0) {
		printf("xbsa_config: %s\n", xbsa_env.xbsa_config);
	}
	if (xbsa_env.instance != 0) {
		printf("instance: %s\n", xbsa_env.instance);
	}
	if (xbsa_env.backup_type != 0) {
		printf("backup_type: %s\n", xbsa_env.backup_type);
	}
	if (xbsa_env.job_type != 0) {
		printf("job_type: %s\n", xbsa_env.job_type);
	}
	free_xbsa_env(&xbsa_env);

	return EXIT_SUCCESS;
}
