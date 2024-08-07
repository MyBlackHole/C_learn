#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

int demo_popen_main(int argc, char *argv[])
{
	FILE *p_fp;
	char buffer[BUFFER_SIZE];

	if (argc!= 2)
	{
		printf("Usage: %s command\n", argv[0]);
		return EXIT_FAILURE;
	}
	p_fp = popen(argv[1], "r");
	/*p_fp = popen("cat /etc/passwd", "r");*/
	// 打印所有内容
	while (fgets(buffer, BUFFER_SIZE, p_fp)!= NULL) {
		printf("%s", buffer);
	}
	pclose(p_fp);
	return EXIT_SUCCESS;
}
