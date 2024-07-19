
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

const char *argp_program_version = "argp_parse_test 1";
const char *argp_program_bug_address = "1358244533@qq.com";

const char *DEFAULT_PATH =
	"/run/media/black/Data/Documents/C/inih_learn/test.ini";

static char doc[] =
	"Argp example #3 -- a program with options and arguments using argp";

static char args_doc[] = "ARG1 ARG2";

static struct argp_option options[] = { { "input", 'c', "FILE", 0, "配置路径" },
					{ 0 } };

struct arguments {
	char *config_file;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

	switch (key) {
	case 'c':
		arguments->config_file = arg;
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

typedef struct {
	int version;
	const char *name;
	const char *email;
} configuration;

static int handler(void *user, const char *section, const char *name,
		   const char *value)
{
	configuration *pconfig = (configuration *)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("protocol", "version")) {
		pconfig->version = atoi(value);
	} else if (MATCH("user", "name")) {
		pconfig->name = strdup(value);
	} else if (MATCH("user", "email")) {
		pconfig->email = strdup(value);
	} else {
		return 0; /* unknown section/name, error */
	}
	return 1;
}

bool is_file(char *fname)
{
	struct stat statres;
	if (stat(fname, &statres) < 0) {
		perror("stat()");
		exit(1);
	}
	printf("statres.st_mode:[%d]\n", statres.st_mode & S_IFREG);
	if (statres.st_mode & S_IFREG) {
		return true;
	}
	return false;
}

int demo_ini1_main(int argc, char *argv[])
{
	struct arguments arguments;

	arguments.config_file = strdup(DEFAULT_PATH);

	/* Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	if (!is_file(arguments.config_file)) {
		fprintf(stderr, "%s error\n", arguments.config_file);
		exit(EXIT_FAILURE);
	}

	configuration config;

	if (ini_parse(arguments.config_file, handler, &config) < 0) {
		printf("Can't load 'test.ini'\n");
		return 1;
	}
	printf("Config loaded from 'test.ini': version=%d, name=%s, email=%s\n",
	       config.version, config.name, config.email);

	free((void *)config.name);
	free((void *)config.email);

	return 0;
}
