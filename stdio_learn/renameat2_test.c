#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int test_rename_noreplace()
{
	int oldfd, newfd = -1;
	char oldpath[] = "/run/media/black/Data/Documents/c/Debug/oldfile1";
	char newpath[] = "/run/media/black/Data/Documents/c/Debug/newfile1";
	oldfd = open(oldpath, O_RDONLY);
	if (oldfd == -1) {
		perror("rename_noreplace open oldfile1 failed");
		return EXIT_FAILURE;
	}
	if (renameat2(oldfd, oldpath, newfd, newpath, RENAME_NOREPLACE) == -1) {
		perror("rename_noreplace renameat2 failed");
		close(oldfd);
		close(newfd);
		return EXIT_FAILURE;
	}
	close(oldfd);
	close(newfd);
	return EXIT_SUCCESS;
}

int test_rename_exchange()
{
	int oldfd, newfd = -1;
	char oldpath[] = "/run/media/black/Data/Documents/c/Debug/oldfile2";
	char newpath[] = "/run/media/black/Data/Documents/c/Debug/newfile2";
	oldfd = open(oldpath, O_RDONLY);
	if (oldfd == -1) {
		perror("rename_exchange open oldfile2 failed");
		return EXIT_FAILURE;
	}
	// 这个文件必须存在，否则会报错
	newfd = open(newpath, O_CREAT | O_WRONLY,
		     S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (newfd == -1) {
		perror("rename_exchange open newfile2 failed");
		close(oldfd);
		return EXIT_FAILURE;
	}
	if (renameat2(oldfd, oldpath, newfd, newpath, RENAME_EXCHANGE) == -1) {
		perror("rename_exchange renameat2 failed");
		close(oldfd);
		close(newfd);
		return EXIT_FAILURE;
	}
	close(oldfd);
	close(newfd);
	return EXIT_SUCCESS;
}

int test_rename_whiteout()
{
	int oldfd, newfd = -1;
	char oldpath[] = "/opt/aio/Debug/oldfile3";
	char newpath[] = "/opt/aio/Debug/newfile3";
	oldfd = open(oldpath, O_RDONLY);
	if (oldfd == -1) {
		perror("rename_whiteout open oldfile3 failed");
		return EXIT_FAILURE;
	}
	if (renameat2(oldfd, oldpath, newfd, newpath, RENAME_WHITEOUT) == -1) {
		perror("rename_whiteout renameat2 failed");
		close(oldfd);
		close(newfd);
		return EXIT_FAILURE;
	}
	close(oldfd);
	close(newfd);
	return EXIT_SUCCESS;
}

int demo_renameat2_main(int argc, char *argv[])
{
	// 会删除原文件
	int ret;
	ret = test_rename_noreplace();
	if (ret == EXIT_SUCCESS) {
		printf("rename_noreplace test passed\n");
	} else {
		printf("rename_noreplace test failed\n");
	}

	// 清空原文件内容, 不会删除原文件
	ret = test_rename_exchange();
	if (ret == EXIT_SUCCESS) {
		printf("rename_exchange test passed\n");
	} else {
		printf("rename_exchange test failed\n");
	}

	// 不会删除原文件，会创建黑名单文件
	// 目的是用于隐藏文件，用于 overlayfs 等技术
	// 使下层同名文件不可见
	ret = test_rename_whiteout();
	if (ret == EXIT_SUCCESS) {
		printf("rename_whiteout test passed\n");
	} else {
		printf("rename_whiteout test failed\n");
	}
	return EXIT_SUCCESS;
}
