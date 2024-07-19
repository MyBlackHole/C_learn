#include <openssl/bio.h>
#include <openssl/evp.h>
#include <stdio.h>

int main(void)
{
	EVP_MD_CTX *ctx = NULL;
	EVP_MD *sha256 = NULL;
	const unsigned char msg[] = { 0x00, 0x01, 0x02, 0x03 };
	unsigned int len = 0;
	unsigned char *outdigest = NULL;

	/* Create a context for the digest operation */
	ctx = EVP_MD_CTX_new();
	if (ctx == NULL)
		goto err;

	/*
     * Fetch the SHA256 algorithm implementation for doing the digest. We're
     * using the "default" library context here (first NULL parameter), and
     * we're not supplying any particular search criteria for our SHA256
     * implementation (second NULL parameter). Any SHA256 implementation will
     * do.
     */
	sha256 = EVP_MD_fetch(NULL, "SHA256", NULL);
	if (sha256 == NULL)
		goto err;

	/* Initialise the digest operation */
	if (!EVP_DigestInit_ex(ctx, sha256, NULL))
		goto err;

	/*
     * Pass the message to be digested. This can be passed in over multiple
     * EVP_DigestUpdate calls if necessary
     */
	if (!EVP_DigestUpdate(ctx, msg, sizeof(msg)))
		goto err;

	/* Allocate the output buffer */
	outdigest = OPENSSL_malloc(EVP_MD_get_size(sha256));
	if (outdigest == NULL)
		goto err;

	/* Now calculate the digest itself */
	if (!EVP_DigestFinal_ex(ctx, outdigest, &len))
		goto err;

	/* Print out the digest result */
	BIO_dump_fp(stdout, outdigest, len);

err:
	/* Clean up all the resources we allocated */
	OPENSSL_free(outdigest);
	EVP_MD_free(sha256);
	EVP_MD_CTX_free(ctx);
}
