#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>

// MD5有128bit(16个char)*SHA1有160bit(20个char)*SHA256有256bit(32个char)*SHA244有244bit(28个char)*SHA512有512bit(64个char)
// //SHA1算法是对MD5算法的升级,计算结果为20字节(160位)，使用方法如下：
// //打开/usr/include/openssl/sha.h这个文件我们可以看到一些函数
// // 初始化 SHA Contex, 成功返回1,失败返回0
// int SHA_Init(SHA_CTX *c);
// // 循环调用此函数,可以将不同的数据加在一起计算SHA1,成功返回1,失败返回0
// int SHA_Update(SHA_CTX *c, const void *data, size_t len);
// // 输出SHA1结果数据,成功返回1,失败返回0
// int SHA_Final(unsigned char *md, SHA_CTX *c);
// // SHA_Init,SHA_Update,SHA_Final三个函数的组合,直接计算出SHA1的值
// unsigned char *SHA(const unsigned char *d, size_t n, unsigned char *md);
// // 内部函数,不需要调用
// void SHA_Transform(SHA_CTX *c, const unsigned char *data);

// //上面的SHA可以改为SHA1，SHA224，SHA256，SHA384，SHA512就可以实现多种加密了

int main()
{
	SHA_CTX stx;
	unsigned char outmd[20]; // 注意这里的字符个数为20
	char buffer[1024];
	char filename[32];
	int len = 0;
	int i;
	FILE *fp = NULL;
	memset(outmd, 0, sizeof(outmd));
	memset(filename, 0, sizeof(filename));
	memset(buffer, 0, sizeof(buffer));
	printf("请输入文件名，用于计算SHA1值:");
	scanf("%s", filename);
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("Can't open file\n");
		return 0;
	}

	SHA1_Init(&stx);
	while ((len = fread(buffer, 1, 1024, fp)) > 0) {
		SHA1_Update(&stx, buffer, len);
		memset(buffer, 0, sizeof(buffer));
	}
	SHA1_Final(outmd, &stx);

	for (i = 0; i < 20; i++) {
		printf("%02X", outmd[i]);
	}
	printf("\n");
	return 0;
}
