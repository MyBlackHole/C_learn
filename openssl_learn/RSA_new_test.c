#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PUB_KEY "./public_key.txt"
#define PRI_KEY "./prive_key.txt"

/*************************
**1---------------创建密钥
**************************/
void creat_key()
{
	RSA *r = RSA_new(); // 初始化RSA结构体
	int bits = 1024;
	BIGNUM *e = BN_new(); // 新生成一个BIGNUM结构
	BN_set_word(e, 65537); // 设置e为65537 

	/***
    **RSA_generate_key_ex:生成一对钥匙
    **参数1：RSA结构         参数2：大小
    **参数3：BIGNUM结构 参数4：一般置空
    ******/
	RSA_generate_key_ex(r, bits, e, NULL);

	/****
    **int RSA_print_fp(FILE *fp, const RSA *r,int offset);
    ** -----将生成的密钥输出到文件 *参数1:文件fp指针 参数2:RSA结构体
    **参数3：打印偏移量offset是为了调整输出格式
    ******/
	// RSA_print_fp(stdout,r,0);

	BIO *out;

	/****
    **BIO *BIO_new_file(const char *filename, const char *mode);
    *****/
	out = BIO_new_file("./prive_key.txt", "wr");

	/***
    **PEM_write_bio_RSAPrivateKey(BIO *bp, RSA *x, const EVP_CIPHER *enc,
    **		unsigned char *kstr, int klen,pem_password_cb *cb, void *u);
    **对RSA结构的RSA私钥进行PEM格式的写处理——————私钥
    *****/
	int ret =
		PEM_write_bio_RSAPrivateKey(out, r, NULL, NULL, 0, NULL, NULL);
	printf("私钥:%d\n", ret);

	/***
    **函数原型是一个宏函数
    **#define BIO_flush(b) (int)BIO_ctrl(b,BIO_CTRL_FLUSH,0,NULL)
    **作用：将BIO内部缓冲区的数据都写出去
    *****/
	BIO_flush(out);
	BIO_free(out);

	out = BIO_new_file("./public_key.txt", "wr");
	// 写入公钥
	ret = PEM_write_bio_RSAPublicKey(out, r);
	printf("公钥:%d\n", ret);
	BIO_flush(out);
	BIO_free(out);

	BN_free(e);
	RSA_free(r);
}

/***************************
**2------------公钥加密
****************************/
char *pub_encryption(char *str, char *pubkey_path)
{
	RSA *rsa = NULL;
	FILE *fp = NULL;
	char *en = NULL;
	int len = 0;
	int rsa_len = 0;

	if ((fp = fopen(pubkey_path, "r")) == NULL) {
		printf("=====1======\n");
		return NULL;
	}

	/* 读取公钥PEM，PUBKEY格式PEM使用PEM_read_RSA_PUBKEY函数 */
	if ((rsa = PEM_read_RSAPublicKey(fp, NULL, NULL, NULL)) == NULL) {
		perror(" PEM_read_RSAPublicKey error");
		fclose(fp);
		printf("=======2====\n");
		return NULL;
	}

	// RSA_print_fp(stdout, rsa, 0);

	len = strlen(str);
	rsa_len = RSA_size(rsa);

	// 为加密后的内容 申请空间（根据秘钥的长度+1）
	en = (char *)malloc(rsa_len + 1);
	memset(en, 0, rsa_len + 1);

	// RSA_public_encrypt-->加解密函数
	// 函数原型：int RSA_public_encrypt(intflen, const unsigned char *from,
	// unsigned har *to, RSA *rsa,int padding); 参数1：密钥长度          参数2：
	// 参数3:为加密后内容申请的空间 参数
	//    参数5:有三种模式
	if (RSA_public_encrypt(rsa_len, (unsigned char *)str,
			       (unsigned char *)en, rsa, RSA_NO_PADDING) < 0) {
		perror(" RSA_public_encrypt error");
		fclose(fp);
		printf("========3===\n");
		return NULL;
	}

	RSA_free(rsa);
	fclose(fp);
	printf("===========en %s \n", en);
	return en;
}

char *my_decrypt(char *str, char *prikey_path)
{
	RSA *rsa = NULL;
	FILE *fp = NULL;
	char *de = NULL;
	int rsa_len = 0;

	if ((fp = fopen(prikey_path, "r")) == NULL) {
		return NULL;
	}

	if ((rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL)) == NULL) {
		perror(" PEM_read_RSAPrivateKey error");
		fclose(fp);
		return NULL;
	}

	// RSA_print_fp(stdout, rsa, 0);

	rsa_len = RSA_size(rsa);

	// 为解密后的内容 申请空间（根据秘钥的长度+1）
	de = (char *)malloc(rsa_len + 1);
	memset(de, 0, rsa_len + 1);

	// 解密函数
	if (RSA_private_decrypt(rsa_len, (unsigned char *)str,
				(unsigned char *)de, rsa, RSA_NO_PADDING) < 0) {
		perror(" RSA_private_decrypt error");
		fclose(fp);
		return NULL;
	}

	RSA_free(rsa);
	fclose(fp);

	return de;
}

int main()
{
	char *source = "hello world!";
	creat_key();
	char *en = NULL;
	char *de = NULL;
	en = pub_encryption(source, PUB_KEY);

	de = my_decrypt(en, PRI_KEY);
	printf("dec is: %s\n", de);

	return 0;
}
