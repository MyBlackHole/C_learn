#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

int create_unique_id(char *id_file)
{
	uuid_t uuid;
	char str[36];
	int fp;
	int ret;
	fp = open(id_file, O_RDWR | O_CREAT, 0644);
	if (fp < 0) {
		perror("open id file failure.");
		ret = -1;
		return ret;
	}
	uuid_generate(uuid);
	uuid_unparse(uuid, str);

	ret = write(fp, str, strlen(str));
	if (ret < 0) {
		perror("write id file failure.");
		ret = -1;
		return ret;
	}
	if (ret != strlen(str)) {
		perror("write id file failure.");
		ret = -1;
		return ret;
	}
	ret = close(fp);
	return ret;
}

// 检测文件是否存在
int file_exist(char *file_name)
{
	int ret;

	ret = access(file_name, F_OK);
	if (ret == 0) {
		return 1;
	} else if (errno == ENOENT) {
		return 0;
	} else {
		perror("access file failure.");
		return -1;
	}
}

int demo_uuid_unparse_main(int argc, char **argv)
{
	char *id_file = "id_file.log";
	int ret;

	if (file_exist(id_file) == 1) {
		printf("id file exist, skip create id.");
		return EXIT_FAILURE;
	}

	ret = create_unique_id(id_file);
	if (ret < 0) {
		perror("create_unique_id failure.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
