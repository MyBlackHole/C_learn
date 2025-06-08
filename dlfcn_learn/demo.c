#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#define LIB_PATH \
	"/media/black/Data/Documents/C/build/linux/x86_64/debug/libadd.so"
// #define LIB_PATH "/root/libadd.so"

typedef int FUNC(int, int);

int demo_demo_main()
{
	void *handle;
	char *error;
	FUNC *func = NULL;

	handle = dlopen(LIB_PATH, RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	dlerror();

	func = (FUNC *)dlsym(handle, "add");

	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	printf("add: %d\n", (*func)(2, 4));

	dlclose(handle);
	exit(EXIT_SUCCESS);
}
