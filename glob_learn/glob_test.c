#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int err_func(const char *errpath, int errno)
{
	puts(errpath);
	fprintf(stderr, "ERROR MSG%s\n", strerror(errno));
	return 0;
}

// 执行
// ./out/obj/glob_learn/glob_test '/*'

int demo_glob_main(int argc, char *argv[])
{
	glob_t globres;
	int err;
	int index;

	if (argc < 2) {
		fprintf(stderr, "<str>");
		exit(1);
	}

	// err = glob(argv[1], 0, NULL, &globres);
	/*err = glob(argv[1], GLOB_TILDE, err_func, &globres);*/
	err = glob(argv[1], GLOB_ERR, err_func, &globres);
	if (err) {
		fprintf(stderr, "ERROR %d\n", err);
		exit(1);
	}

	for (index = 0; index < globres.gl_pathc; index++) {
		printf("%s\n", globres.gl_pathv[index]);
	}
	globfree(&globres);
	return 0;
}

// out:

// xmake run glob_learn glob '/run/media/black/Data/Documents/C/y???_learn'
// /run/media/black/Data/Documents/C/yacc_learn
// /run/media/black/Data/Documents/C/yajl_learn
//
// xmake run glob_learn glob '/run/media/black/Data/Documents/C/y???_*'
// /run/media/black/Data/Documents/C/yacc_learn
// /run/media/black/Data/Documents/C/yajl_learn
