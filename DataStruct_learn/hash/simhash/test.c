#include <stdio.h>
#include <stdlib.h>

#include "simhash.h"

int main(int argc, char *argv[])
{
	char *a = "我";
	char *b = "喜欢";
	char *c = "吃";
	char *d = "鸭梨";

	char *x = "我";
	char *y = "爱";
	char *z = "吃";
	char *w = "梨";

	const char **test = malloc(sizeof(char **) * 8);
	test[0] = a, test[1] = b, test[2] = c, test[3] = d;
	test[4] = x, test[5] = y, test[6] = z, test[7] = w;
	ul_int hash1 = sh_simhash(test, 4);
	ul_int hash2 = sh_simhash(test, 4);
	float similarity = 0.0f;
	if (hash1 < hash2) {
		similarity = hash1 * 1.0f / hash2;
	} else {
		similarity = hash2 * 1.0f / hash1;
	}
	printf("hash1=%lx, hash2=%lx, similarity=%f\n", hash1, hash2,
	       similarity);
	exit(0);
}
