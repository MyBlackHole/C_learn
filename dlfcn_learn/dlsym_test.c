#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int demo_dlsym_test_main(int argc, char **argv)
{
	void *handle;
	double (*cosine)(double);
	char *error;

	handle = dlopen("libm.so", RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	dlerror(); /* Clear any existing error */

	/* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
        would seem more natural, but the C99 standard leaves
        casting from "void *" to a function pointer undefined.
        The assignment used below is the POSIX.1-2003 (Technical
        Corrigendum 1) workaround; see the Rationale for the
        POSIX specification of dlsym(). */

	*(void **)(&cosine) = dlsym(handle, "cos");
	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}

	printf("%f\n", (*cosine)(2.0));
	dlclose(handle);
	exit(EXIT_SUCCESS);
}
