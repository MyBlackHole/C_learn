#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

const char base62_chars[62] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
	'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c',
	'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
	'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
};

const char keys[24][62] = {
	"lBYL0Sqg8uG5prFRhEP1mdWJiNjzUCM9noDw6Q37ty4OacKZIeV2TXxAkHbvsf",
	"jYyaTSfUbrGvulAn2LgWV3Dw1pMtBZhmq9X5Q8Fe6ik4oP07EcxRKCIsHOJzNd",
	"1Jy3MUFrnaPIRDg09iTYAomvk6tfdbWVhE82zcLwS4Bqs5XGjQCNxeKHZ7uOlp",
	"wZqty9WM2XiLuREjU56PVapK8z4B0FgDoCHmOknTbcrSIvx3YdhQAlsNef7GJ1",
	"S1JIuUEHYC678ftjKxWDXkzRhG45sv9PFQNwlTB3Lgr0m2eynVcipdZaAMqbOo",
	"xOgZr051fWh8b4jVNSMaIDnUzmCLEPBXvAG2iF93tTkKsHdpq6yoweRucJYl7Q",
	"dcanJKS2U9Z1gDy0me34xsYQwzXfClMqkNLrpijH6IP7tOW8AhE5RVGoFvBbTu",
	"IzYk260ivfHjhNVTGws8AyXur7UESnba1FL9K3cCM4WtdqOgmopx5JRlPZDeBQ",
	"7pYMZf8wztSGPbligIas3d59y1mAqTNVvXUQBRkKJh0DOe4rCjcLnx6HoEFu2W",
	"kUyNEiDLT9IOv5K0rPF1e6Bt4aQqYbudJCxMRoG23HW78AVZmgSnzXfhlcwjsp",
	"gv6fKjTSLGX52OYt7harx3Jolw9BnuFpdHbNzc1UIsRDAM40qZeV8ikPEQmWyC",
	"0TKXMpBVgrxkWlZqJHQi8zwfFeUDs62I9CNhGv5bo3n47mOYuPjRcL1dSyAtaE",
	"XuM0oCJveK7hzPWNYTqDgRl56fnbZys2BVk3LIOE89ijGaF4QAdcmrUStwHp1x",
	"WcVeEqfTpFABL9XOCkJj5Ri8UuwaGsmZzl4ny3gtrxD7dYSb1vKN2QMoP6I0hH",
	"OsEF8HMxWKYZfBQLhnoXAT67Uqlu9tRgjybGk5mCvazJpr3NidP0DI4S2V1cew",
	"3ruNBize49TZHPl60pwUfEb1CgRSqMoKyIdQAnkYFaV7LXGDsJmWh2cxO5jvt8",
	"35TSE6cyLvkYQnpGuD8aJhCH0tBR1WN94eFKOPZbUxogfV2sziIljm7drwMAXq",
	"ZDWUCmzytXEdFouHMnRG0YSb58sklj1J43fALqOVwph6vKeBTQ2gr7i9PcaxNI",
	"hZvXd2AQJMcBF4wfuIeya0CjTzOnRro9s75qxmbW6P3tEGSg8KDp1ULHYNkliV",
	"AylrtUkmdgiL02xXeTM7CJva3n6HcoEDQbOPVWBY5u9Fpzfwq8R4jsSIh1ZNGK",
	"pePQ8bqzZB3KM7Uh5FfcJNRGjdnmYxk6DXrT0EC2S1WlioaIV9uLOwtv4HgsAy",
	"wuyVEWkqLt79gRoBai18vrQdcTAJDUSM5p40fj6nFIKzPOZhHYX2sembN3GxCl",
	"egf9VOXh4WqEUcKTIu1sBYobrGjp5d7H3xZiDvC0aLQnkMRPmwty6J82AzlFNS",
	"pLxifohA4MPDTGsy5Wblkw197dO8reRgB3E0QYa6NmVS2InUuJZcCqvtHjXFzK",
};

void init_crypto_table(char **keys)
{
	char encrypt_table[62]; // 加密字符表

	memcpy(encrypt_table, base62_chars, 62);

	for (int i = 0; i < 24; i++) {
		// 使用Fisher-Yates洗牌算法打乱加密表
		for (int i = 61; i > 0; i--) {
			int j = rand() % (i + 1);
			char temp = encrypt_table[i];
			encrypt_table[i] = encrypt_table[j];
			encrypt_table[j] = temp;
		}

		strcpy(keys[i], encrypt_table);
		printf("%s\n", encrypt_table);
	}
}

void encrypt_string(const char *input, char *output, size_t length)
{
	int tm_hour = 0;
	time_t rawtime;
	const char *key;
	struct tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	tm_hour = timeinfo->tm_hour;
	key = keys[tm_hour];
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < 62; j++) {
			if (input[i] == key[j]) {
				output[i] = key[(j + tm_hour) % 62];
				break;
			}
		}
	}
}

void decrypt_string(const char *input, char *output, size_t length)
{
	int tm_hour = 0;
	time_t rawtime;
	const char *key;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	tm_hour = timeinfo->tm_hour;
	key = keys[tm_hour];
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < 62; j++) {
			if (input[i] == key[j]) {
				output[i] = key[(j - tm_hour + 62) % 62];
				break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	char input[100] = "Helloworld";
	char output[100] = { 0 };
	size_t length = strlen(input);

	char *keys_tmp[24];
	for (int i = 0; i < 24; i++) {
		keys_tmp[i] = (char *)malloc(62 * sizeof(char));
	}
	init_crypto_table(keys_tmp);

	encrypt_string(input, output, length);
	printf("Encrypt: %s\n", output);

	decrypt_string(output, output, length);
	printf("Decrypt: %s\n", output);

	for (int i = 0; i < 24; i++) {
		free(keys_tmp[i]);
	}
	return EXIT_SUCCESS;
}
