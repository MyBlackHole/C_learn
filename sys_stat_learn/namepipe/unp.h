#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 512
#define ERR_EXIT(sz)                \
	do {                        \
		perror(sz);         \
		exit(EXIT_FAILURE); \
	} while (0)

#define write_fifo "write_fifo"
#define read_fifo "read_fifo"
