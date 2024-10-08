#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "page.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s <page_file> <page_size>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int ret = EXIT_SUCCESS;
	char *page_file = argv[1];
	int page_size = atoi(argv[2]);
	int fd = open(page_file, O_RDONLY);
	PageHeaderData *page_header = NULL;
	if (fd < 0) {
		perror("Failed to open page file");
		ret = errno;
		goto err1_;
	}

	char *page = malloc(page_size);
	if (page == NULL) {
		perror("Failed to allocate memory for page");
		ret = errno;
		goto err2_;
	}

	while (1) {
		ssize_t nread = read(fd, page, page_size);
		if (nread == 0) {
			break;
		}
		if (nread < 0) {
			perror("Failed to read page from file");
			ret = errno;
			goto err3_;
		}
		if (nread != page_size) {
			fprintf(stderr,
				"Failed to read full page from file: %zd bytes read, %d bytes expected\n",
				nread, page_size);
			ret = EIO;
			goto err3_;
		}
		page_header = (PageHeaderData *)page;
		if (page_header->pd_special == page_size &&
		    page_header->pd_pagesize_version > page_size) {
			continue;
		} else {
			ret = EXIT_FAILURE;
			break;
		}
	}

err3_:
	free(page);
err2_:
	close(fd);
err1_:
	return ret;
}
