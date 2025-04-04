#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <lz4.h>

int demo_LZ4_decompress_safe_main(int argc, char **argv)
{
	int ret = 0;
	char *src_file = NULL;
	int s_fd = 0;
	char *src_buffer = NULL;
	char *dst_file = NULL;
	int d_fd = 0;
	char *dst_buffer = NULL;
	size_t src_offset = 0;
	size_t src_size = 0;
	size_t dst_size = 0;

	if (argc < 6) {
		printf("Usage: %s <src_file> <src_offset> <src_size> <dst_file> <dst_size>\n",
		       argv[0]);
		return EXIT_FAILURE;
	}
	src_file = argv[1];
	src_offset = atoi(argv[2]);
	src_size = atoi(argv[3]);
	dst_file = argv[4];
	dst_size = atoi(argv[5]);

	src_buffer = malloc(src_size);
	if (src_buffer == NULL) {
		printf("Failed to allocate src_buffer\n");
		ret = -EXIT_FAILURE;
		goto exit;
	}
	dst_buffer = malloc(dst_size);
	if (dst_buffer == NULL) {
		printf("Failed to allocate dst_buffer\n");
		ret = -EXIT_FAILURE;
		goto free_src_buffer;
	}

	s_fd = open(src_file, O_RDONLY);
	if (s_fd < 0) {
		printf("Failed to open src_file: %s\n", src_file);
		ret = -EXIT_FAILURE;
		goto free_dst_buffer;
	}
	lseek(s_fd, src_offset, SEEK_SET);
	if (read(s_fd, src_buffer, src_size) != src_size) {
		printf("Failed to read src_file: %s\n", src_file);
		ret = -EXIT_FAILURE;
		goto close_src_fd;
	}

	d_fd = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d_fd < 0) {
		printf("Failed to open dst_file: %s\n", dst_file);
		ret = -EXIT_FAILURE;
		goto close_src_fd;
	}

	dst_size =
		LZ4_decompress_safe(src_buffer, dst_buffer, src_size, dst_size);
	if (dst_size == 0) {
		printf("Failed to decompress src_file: %s\n", src_file);
		ret = -EXIT_FAILURE;
		goto close_dst_fd;
	}
	printf("Decompressed %lu bytes from %s to %s\n", dst_size, src_file,
	       dst_file);
	if (write(d_fd, dst_buffer, dst_size) != dst_size) {
		printf("Failed to write dst_file: %s\n", dst_file);
		ret = -EXIT_FAILURE;
		goto close_dst_fd;
	}
close_dst_fd:
	close(d_fd);
close_src_fd:
	close(s_fd);
free_dst_buffer:
	free(dst_buffer);
free_src_buffer:
	free(src_buffer);
exit:
	return ret;
}
