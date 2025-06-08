/* Dependencies */
#include <stdio.h> // For printf()
#include <stdlib.h> // For exit()
#include <string.h> // For memcmp()

#include <lz4.h> // This is all that is required to expose the prototypes for basic compression and decompression.
#include <lz4hc.h> // This is all that is required to expose the prototypes for basic compression and decompression.
#include <unistd.h>

/*
 * Simple show-error-and-bail function.
 */
void run_screaming(const char *message, const int code);

/*
 * main
 */
int demo_LZ4_compress_HC_main(void)
{
	// const char * const src =
	//     "Lorem ipsum dolor sit amet, consectetur adipiscing "
	//     "elit. Lorem ipsum dolor site amat.";
	const char *const src =
		"/gaussdb/data/my_tbs/PG_9.2_201611171_dn_6001_6002_6003/18710/"
		"18714_fsm";
	const int src_size = (int)(strlen(src) + 1);
	const int max_dst_size = LZ4_compressBound(src_size);
	char *compressed_data = (char *)malloc((size_t)max_dst_size);
	if (compressed_data == NULL) {
		run_screaming("Failed to allocate memory for *compressed_data.",
			      1);
	}
	const int compressed_data_size = LZ4_compress_HC(src, compressed_data,
							 src_size, max_dst_size,
							 LZ4HC_CLEVEL_DEFAULT);
	if (compressed_data_size <= 0) {
		run_screaming(
			"A 0 or negative result from LZ4_compress_HC() "
			"indicates a failure trying to compress the data. ",
			1);
	}
	if (compressed_data_size > 0) {
		printf("We successfully compressed some data! Ratio: %.2f\n",
		       (float)compressed_data_size / src_size);
	}
	compressed_data =
		(char *)realloc(compressed_data, (size_t)compressed_data_size);
	if (compressed_data == NULL) {
		run_screaming(
			"Failed to re-alloc memory for compressed_data.  Sad :(",
			1);
	}
	// printf("src: [%.*s]\n", 10, src);
	printf("src: [%s]\n", src);

	putchar('[');
	fflush(stdout);
	// printf("[%.*s]\n", compressed_data_size, compressed_data);
	if (write(STDOUT_FILENO, compressed_data, compressed_data_size) !=
	    compressed_data_size) {
		run_screaming("write error.", 1);
	}
	putchar(']');
	putchar('\n');
	char *const regen_buffer = (char *)malloc(src_size);
	if (regen_buffer == NULL) {
		run_screaming("Failed to allocate memory for *regen_buffer.",
			      1);
	}
	const int decompressed_size = LZ4_decompress_safe(
		compressed_data, regen_buffer, compressed_data_size, src_size);
	free(compressed_data); /* no longer useful */
	if (decompressed_size < 0) {
		run_screaming(
			"A negative result from LZ4_decompress_safe indicates a failure "
			"trying "
			"to decompress the data.  See exit code (echo $?) for value "
			"returned.",
			decompressed_size);
	}
	if (decompressed_size >= 0) {
		printf("We successfully decompressed some data!\n");
	}
	if (decompressed_size != src_size) {
		run_screaming(
			"Decompressed data is different from original! \n", 1);
	}

	/* Validation */
	// We should be able to compare our original *src with our *new_src and be
	// byte-for-byte identical.
	if (memcmp(src, regen_buffer, src_size) != 0) {
		run_screaming(
			"Validation failed.  *src and *new_src are not identical.",
			1);
		printf("Validation done. The string we ended up with is:\n%s\n",
		       regen_buffer);
	}
	return 0;
}
