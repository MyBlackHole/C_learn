#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_getopt_main(int argc, char *argv[])
{
	int item;
	printf("\n\n");
	printf("optind:%d，opterr：%d\n", optind, opterr);
	printf("--------------------------\n");
	while ((item = getopt(argc, argv, "ab:c:de::")) != -1) {
		printf("optind: %d\n", optind);
		switch (item) {
		case 'a':
			printf("HAVE option: -a\n\n");
			break;
		case 'b':
			printf("HAVE option: -b\n");
			printf("The argument of -b is %s\n\n", optarg);
			break;
		case 'c':
			printf("HAVE option: -c\n");
			printf("The argument of -c is %s\n\n", optarg);
			break;
		case 'd':
			printf("HAVE option: -d\n");
			break;
		case 'e':
			printf("HAVE option: -e\n");
			printf("The argument of -e is %s\n\n", optarg);
			break;
		case '?':
			printf("Unknown option: %c\n", (char)optopt);
			break;
		default:
			printf("Unknown option: %c\n", (char)optopt);
		}
	}
	return EXIT_SUCCESS;
}
