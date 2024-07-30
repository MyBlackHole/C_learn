#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int hex2bin(const char *hex, unsigned char *bin, const int length)
{
	int i = 0;
	int t = 0;
	int bytes = 0;
	for (i = 0; i < length; i += 2, ++bytes) {
		bin[bytes] = 0x00;
		for (t = 0; t < 2; ++t) {
			if ('0' <= hex[i + t] && hex[i + t] <= '9') {
				bin[bytes] += hex[i + t] - '0';
			} else if ('a' <= hex[i + t] && hex[i + t] <= 'f') {
				bin[bytes] += hex[i + t] - 'a' + 10;
			} else if ('A' <= hex[i + t] && hex[i + t] <= 'F') {
				bin[bytes] += hex[i + t] - 'A' + 10;
			}
			if (0 == t) {
				//height 4 bit
				bin[bytes] = (bin[bytes] << 4);
			}
		}
	}

	// return bytes;
	printf("%s\n", hex);
	for (int j = 0; j < bytes; ++j) {
		printf("%02x", bin[j]);
	}
	printf("\n");

	return bytes;
}

int hex2bin2(const char *hex, unsigned char *bin, const int length)
{
	int i = 0;
	int j = 1;
	int bytes = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X')) {
		hex += 2;
	}
	for (i = 0, j = 1; j < length; i += 2, j += 2, ++bytes) {
		bin[bytes] =
			((('0' <= hex[i] && hex[i] <= '9') ?
				  (hex[i] - '0') :
				  (('a' <= hex[i] && hex[i] <= 'f') ?
					   (hex[i] - 'a' + 10) :
					   (('A' <= hex[i] && hex[i] <= 'F') ?
						    (hex[i] - 'A' + 10) :
						    0)))
			 << 4) +
			(('0' <= hex[j] && hex[j] <= '9') ?
				 (hex[j] - '0') :
				 (('a' <= hex[j] && hex[j] <= 'f') ?
					  (hex[j] - 'a' + 10) :
					  (('A' <= hex[j] && hex[j] <= 'F') ?
						   (hex[j] - 'A' + 10) :
						   0)));
	}

	// return bytes;
	printf("src:%s\n", hex);
	printf("dst:");
	for (int j = 0; j < bytes; ++j) {
		printf("%02x", bin[j]);
	}
	printf("\n");

	return bytes;
}

int main(int argc, char *argv[])
{
	printf("hex16\n");
	const char *hex = "61646d696e";
	char buff[4096] = {};
	printf("hex2bin:%d\n", hex2bin2(hex, (unsigned char *)buff, strlen(hex)));
	printf("%s\n", buff);
	memset(buff, 0, sizeof(buff));
	printf("hex2bin:%d\n", hex2bin(hex, (unsigned char *)buff, strlen(hex)));
	printf("%s\n", buff);
	return EXIT_SUCCESS;
}
