#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include "plugin.h"

typedef void (*init_plugin_function)();

void mfp_register(const char *name)
{
	fprintf(stderr, "Registered plugin \"%s\"\n", name);
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		fprintf(stderr, "Usage: %s [plugin1] [plugin2] ...\n", argv[0]);
		return 0;
	}

	uv_lib_t *lib = (uv_lib_t *)malloc(sizeof(uv_lib_t));
	while (--argc) {
		fprintf(stderr, "Loading %s\n", argv[argc]);
		if (uv_dlopen(argv[argc], lib)) {
			fprintf(stderr, "Error: %s\n", uv_dlerror(lib));
			continue;
		}

		init_plugin_function init_plugin;
		if (uv_dlsym(lib, "initialize", (void **)&init_plugin)) {
			fprintf(stderr, "dlsym error: %s\n", uv_dlerror(lib));
			continue;
		}

		fprintf(stderr, "run %s initialize()\n", argv[argc]);
		init_plugin();
	}

	return 0;
}
