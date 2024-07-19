#include <stdio.h>
#include <stdlib.h>

int main()
{
	char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
	char *pnd;
	long int li1, li2, li3, li4;
	li1 = strtol(szNumbers, &pnd, 10);
	printf("[2001]转换成10进制: %ld\n", li1);
	printf("[pnd]%s\n", pnd);
	printf("[&pnd]%p\n\n", pnd);
	li2 = strtol(pnd, &pnd, 16);
	printf("[60c0c0]转换成10进制: %ld\n", li2);
	printf("[pnd]%s\n", pnd);
	printf("[&pnd]%p\n\n", pnd);
	li3 = strtol(pnd, &pnd, 2);
	printf("[-1101110100110100100000]转换成10进制: %ld\n", li3);
	printf("[pnd]%s\n", pnd);
	printf("[&pnd]%p\n\n", pnd);
	li4 = strtol(pnd, NULL, 0);
	printf("[0x6fffff]转换成10进制: %ld\n", li4);
	printf("[pnd]%s\n", pnd);
	printf("[&pnd]%p\n\n", pnd);

	unsigned long int test = strtol("FFFFFFFFFFFFFFFF", NULL, 16);

	printf("test:[%lx]\n", test);
	printf("test:[%ld]\n", sizeof(long int));

	return 0;
}
