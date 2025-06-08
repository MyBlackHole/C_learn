#include <stdio.h>
#include <strings.h>

int main()
{
	struct {
		int a;
		char s[5];
		float f;
	} tt;
	char s[20];
	bzero(&tt, sizeof(tt)); // structinitializationtozero
	bzero(s, 20);
	printf("InitailSuccess");
	return 0;
}
