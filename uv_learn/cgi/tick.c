#include <stdio.h>
#include <unistd.h>

int main()
{
	int index;
	for (index = 0; index < 10; index++) {
		printf("tick\n");
		fflush(stdout);
		sleep(1);
	}
	printf("BOOM!\n");
	return 0;
}
