#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

// 设置随机数种子（密钥）
void set_encryption_key(unsigned int seed)
{
	srand(seed); // 初始化随机数生成器
}

// 使用随机位反转模式加密一个字节
uint8_t encrypt_byte(uint8_t byte)
{
	// 生成随机位反转模式 (0-255)
	uint8_t pattern = rand() & 0xFF;

	// 应用位反转
	return byte ^ pattern;
}

// 使用随机位反转模式解密一个字节
uint8_t decrypt_byte(uint8_t byte)
{
	// 生成相同的随机位反转模式
	uint8_t pattern = rand() & 0xFF;

	// 应用相同的位反转进行解密
	return byte ^ pattern;
}

// 加密字符串
void encrypt_string(const char *input, char *output, size_t length)
{
	for (size_t i = 0; i < length; i++) {
		output[i] = encrypt_byte(input[i]);
	}
}

// 解密字符串
void decrypt_string(const char *input, char *output, size_t length)
{
	for (size_t i = 0; i < length; i++) {
		output[i] = decrypt_byte(input[i]);
	}
}

// 加密文件
void encrypt_file(const char *input_filename, const char *output_filename)
{
	FILE *in_file = fopen(input_filename, "rb");
	FILE *out_file = fopen(output_filename, "wb");

	if (!in_file || !out_file) {
		perror("文件打开错误");
		exit(EXIT_FAILURE);
	}

	uint8_t byte;
	while (fread(&byte, 1, 1, in_file)) {
		uint8_t encrypted = encrypt_byte(byte);
		fwrite(&encrypted, 1, 1, out_file);
	}

	fclose(in_file);
	fclose(out_file);
}

// 解密文件
void decrypt_file(const char *input_filename, const char *output_filename)
{
	FILE *in_file = fopen(input_filename, "rb");
	FILE *out_file = fopen(output_filename, "wb");

	if (!in_file || !out_file) {
		perror("文件打开错误");
		exit(EXIT_FAILURE);
	}

	uint8_t byte;
	while (fread(&byte, 1, 1, in_file)) {
		uint8_t decrypted = decrypt_byte(byte);
		fwrite(&decrypted, 1, 1, out_file);
	}

	fclose(in_file);
	fclose(out_file);
}

// 可视化字节的位模式
void print_binary(uint8_t byte)
{
	for (int i = 7; i >= 0; i--) {
		printf("%d", (byte >> i) & 1);
	}
}

// 可视化加密过程
void visualize_encryption(uint8_t original, const char *label)
{
	uint8_t pattern = rand() & 0xFF;
	uint8_t encrypted = original ^ pattern;

	printf("\n%s加密过程:\n", label);
	printf("原始数据: ");
	print_binary(original);
	printf(" (0x%02X)\n", original);

	printf("随机模式: ");
	print_binary(pattern);
	printf("\n");

	printf("加密结果: ");
	print_binary(encrypted);
	printf(" (0x%02X)\n", encrypted);

	// 重置随机数序列（为了演示）
	uint8_t temp = decrypt_byte(encrypted);
	(void)temp; // 避免未使用变量警告
}

int main()
{
	// 设置加密密钥（可以是任意整数）
	unsigned int key = 0xDEADBEEF;
	set_encryption_key(key);

	// 演示字符串加密
	// const char *original_str = "rdb-16CB";
	const char *original_str = "dba16CB";
	// const char *original_str = "Hello, World!";
	size_t len = strlen(original_str); // 包含结束符

	char encrypted_str[256] = { 0 };
	char decrypted_str[256] = { 0 };

	encrypt_string(original_str, encrypted_str, len);
	// 重置随机数生成器（使用相同密钥）
	set_encryption_key(key);
	decrypt_string(encrypted_str, decrypted_str, len);

	printf("\n字符串加密演示:\n");
	printf("原始字符串: %s\n", original_str);
	printf("加密后内容: ");
	for (size_t i = 0; i < len; i++) {
		printf("%02X ", (unsigned char)encrypted_str[i]);
	}
	printf("\n");
	printf("加密后字符串: [%s]\n", encrypted_str);
	printf("解密后字符串: %s\n", decrypted_str);

	// // 可视化单个字节的加密过程
	// set_encryption_key(key);
	// visualize_encryption('A', "字符'A'");
	//
	// set_encryption_key(key);
	// visualize_encryption(0x55, "模式0x55");
	//
	// set_encryption_key(key);
	// visualize_encryption(0xAA, "模式0xAA");

	// // 文件加密演示
	// printf("\n文件加密演示:\n");
	//
	// // 创建测试文件
	// FILE *test_file = fopen("test.txt", "w");
	// if (test_file) {
	// 	fprintf(test_file, "This is a secret file!\n");
	// 	fclose(test_file);
	// 	printf("已创建测试文件: test.txt\n");
	// }
	//
	// // 加密文件
	// set_encryption_key(key);
	// encrypt_file("test.txt", "test.enc");
	// printf("已加密文件: test.enc\n");
	//
	// // 解密文件
	// set_encryption_key(key);
	// decrypt_file("test.enc", "test_dec.txt");
	// printf("已解密文件: test_dec.txt\n");
	//
	// // 检查文件内容
	// printf("\n解密文件内容:\n");
	// FILE *dec_file = fopen("test_dec.txt", "r");
	// if (dec_file) {
	// 	char line[256];
	// 	while (fgets(line, sizeof(line), dec_file)) {
	// 		printf("%s", line);
	// 	}
	// 	fclose(dec_file);
	// }

	return 0;
}

// 字符串加密演示:
// 原始字符串: dba-16CB
// 加密后内容: 85 50 77 68 4C 07 56 B4
// 加密后字符串: [PwhLV]
// 解密后字符串: dba-16CB
