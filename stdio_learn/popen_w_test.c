#include <stdlib.h>
#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>

/*#define BUFFER_SIZE 165536*/
/*#define BUFFER_SIZE 65536*/
#define BUFFER_SIZE 4096
/*#define BUFFER_SIZE 64*/

// 测试 xbstream -x -C /opt/aio/xtrabackup/xbstream_full_test1 异常后是否可以继续写入
int demo_popen_w_main(int argc, char *argv[])
{
	FILE *p_fp;
	int fd_in;
	char buffer[BUFFER_SIZE];
	int read_len = 0;
	int write_len = 0;

	if (argc != 3) {
		printf("Usage: %s <input_file> <command>\n", argv[0]);
		return EXIT_FAILURE;
	}

	p_fp = popen(argv[2], "w");
	if (p_fp == NULL) {
		printf("Failed to open pipe\n");
		return EXIT_FAILURE;
	}

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0) {
		printf("Failed to open input file\n");
		return EXIT_FAILURE;
	}

	while (true) {
		read_len = read(fd_in, buffer, BUFFER_SIZE);
		if (read_len < 0) {
			printf("Failed to read from input file; read_len = %d\n", read_len);
			break;
		}
		if (read_len == 0) {
			printf("Read from input file completed; read_len = %d\n", read_len);
			break;
		}
		write_len = fwrite(buffer, 1, BUFFER_SIZE, p_fp);
		if (write_len != read_len) {
			printf("Failed to write to pipe; write_len = %d, read_len = %d\n", write_len, read_len);
			break;
		}
	}

	pclose(p_fp);
	return EXIT_SUCCESS;
}

/*❯ ls -alh /opt/aio/xtrabackup/xbstream_full_test1*/
/*Permissions Size User  Date Modified Name*/
/*.rw-r-----   447 black 14 Aug 10:55   backup-my.cnf*/
/*.rw-r-----   158 black 14 Aug 10:55   binlog.000012*/
/*.rw-r-----    16 black 14 Aug 10:55   binlog.index*/
/*.rw-r-----  6.2k black 14 Aug 10:55   ib_buffer_pool*/
/*.rw-r-----   13M black 14 Aug 10:55   ibdata1*/
/*drwxr-x---     - black 14 Aug 10:55   mysql*/
/*.rw-r-----   27M black 14 Aug 10:55   mysql.ibd*/
/*drwxr-x---     - black 14 Aug 10:55   performance_schema*/
/*drwxr-x---     - black 14 Aug 10:55   sys*/
/*.rw-r-----   17M black 14 Aug 10:55   undo_001*/
/*.rw-r-----   17M black 14 Aug 10:55   undo_002*/
/*.rw-r-----    18 black 14 Aug 10:55   xtrabackup_binlog_info*/
/*.rw-r-----   134 black 14 Aug 10:55   xtrabackup_checkpoints*/
/*.rw-r-----   596 black 14 Aug 10:55   xtrabackup_info*/
/*.rw-r-----  2.6k black 14 Aug 10:55   xtrabackup_logfile*/
/*.rw-r-----    39 black 14 Aug 10:55   xtrabackup_tablespaces*/

/*output: 会立即失败*/
/**/
/*xmake run stdio_learn popen_w /opt/aio/xtrabackup/backup.xbstream "xbstream -x -C /opt/aio/xtrabackup/xbstream_full_test1"*/
/*xbstream: Can't create/write to file './ibdata1' (OS errno 17 - File exists)*/
/*xbstream: failed to create file.*/
/*exit code: 1*/
/*Failed to write to pipe; write_len = 0, read_len = 4096*/
