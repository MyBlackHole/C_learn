#include <inttypes.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	const uint64_t h = 1000001231230u;
	uint8_t hash[20];
	SHA1((const unsigned char *)(&h), 8, hash);
	printf("%s\n", hash);
	exit(0);
}
