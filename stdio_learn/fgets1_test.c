#include <stdio.h>
#include <stdlib.h>

#define NUM 1000;

int demo_fgets1_main(int argc, char *argv[])
{
	int len = NUM;
	char buf[len];

	FILE *fp_tmp = fopen(argv[1], "r");
	if (fp_tmp == NULL) {
		perror("fopen()");
		exit(1);
	}

	while (fgets(buf, len, fp_tmp)) {
		printf("%s\n", buf);
	}
	return 0;
}
