#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM 5

int demo_strncmp1_test_main()
{
	int idx;
	/*char path[] =*/
	/*	"/appDxc/A/C;/appDxc3/A;/appDxc/C;/appDxc/B;/appDxc2/A/C;";*/
	char *path = "/appDxc4/A/D.txt";
	char *paths[NUM];
	paths[0] = "/appDxc/A/C";
	paths[1] = "/appDxc3/A";
	paths[2] = "/appDxc/C";
	paths[3] = "/appDxc/B";
	paths[4] = "/appDxc2/A/C";
	for (idx = 0; idx < NUM; ++idx) {
		printf("%s\n", paths[idx]);
		if (paths[idx]) {
			if (strncmp(paths[idx], path, strlen(paths[idx])) ==
			    0) {
				printf("%s\n", paths[idx]);
				return 0;
			}
		}
	}
	return EXIT_SUCCESS;
}
