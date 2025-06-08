#include <sodium.h>
#include <stddef.h>

int main(int argc, char *argv[])
{
	size_t bin_len;
	unsigned char bin[6];
	unsigned char b64[9] = "aGVsbG8=";
	sodium_base642bin(bin, sizeof bin, (char *)b64, (size_t)(b64), "",
			  &bin_len, NULL, sodium_base64_VARIANT_ORIGINAL);
	printf("%ld: %s\n", bin_len, bin);
	return 0;
}
