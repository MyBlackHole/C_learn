
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

const char *DEFAULT_PATH2 =
	"/run/media/black/Data/Documents/C/inih_learn/xbsa_gaussdb_backup.conf";

struct arguments {
	char *config_file;
};

typedef struct {
	int version;
	const char *logfile;
	const char *storagepath;
} configuration2;

static int handler2(void *user, const char *section, const char *name,
		    const char *value)
{
	configuration2 *pconfig = (configuration2 *)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("protocol", "version")) {
		pconfig->version = atoi(value);
	} else if (MATCH("", "logfile")) {
		pconfig->logfile = strdup(value);
	} else if (MATCH("", "storagepath")) {
		pconfig->storagepath = strdup(value);
	} else {
		return 0; /* unknown section/name, error */
	}
	return 1;
}

bool is_file(char *fname);

int demo_ini2_main(int argc, char *argv[])
{
	struct arguments arguments;

	arguments.config_file = strdup(DEFAULT_PATH2);

	if (!is_file(arguments.config_file)) {
		fprintf(stderr, "%s error\n", arguments.config_file);
		exit(EXIT_FAILURE);
	}

	configuration2 config;

	if (ini_parse(arguments.config_file, handler2, &config) < 0) {
		printf("Can't load 'xbsa_gaussdb_backup.conf'\n");
		return EXIT_FAILURE;
	}
	printf("Config loaded from 'xbsa_gaussdb_backup.conf': version=%d, "
	       "logfile=%s, "
	       "storagepath=%s\n",
	       config.version, config.logfile, config.storagepath);

	free((void *)config.logfile);
	free((void *)config.storagepath);

	return 0;
}
