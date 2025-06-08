#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int demo_crypt_main()
{
	char passwd[13];
	char *key;
	char slat[2];
	key = getpass("Input First Password:");
	slat[0] = key[0];
	slat[1] = key[1];
	strcpy(passwd, crypt(key, slat));
	key = getpass("Input Second Password:");
	slat[0] = passwd[0];
	slat[1] = passwd[1];
	printf("After crypt(),1s t passwd:%s\n", passwd);
	printf("After crypt(),2n d passwd:%s\n", crypt(key, slat));
	return EXIT_SUCCESS;
}
