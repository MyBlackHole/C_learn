#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int demo_lockf_main()
{
	int pid1;
	int pid2;
	int index;
	while ((pid1 = fork()) == -1) {
		; // 创建子进程p1，这个是一个技巧，直到创建子进程成功为止
	}
	if (pid1 == 0) {
		lockf(1, 1, 0); // 加锁第一个参数为stdout（标准输出设备描述符）
		// printf("child  %4d %4d\n",getppid(),getpid(),p1);
		for (index = 0; index < 5; index++) {
			printf("daughter%d\n", index);
		}
		lockf(1, 0, 0);
	} else {
		while ((pid2 = fork()) == -1) {
			; // 创建子进程p2
		}
		if (pid2 == 0) {
			lockf(1, 1,
			      0); // 加锁第一个参数为stdout（标准输出设备描述符）
			for (index = 0; index < 5; index++) {
				printf("son%d\n", index);
			}
			lockf(1, 0, 0); // 解锁
		} else {
			lockf(1, 1, 0); // 加锁
			for (index = 0; index < 5; index++) {
				printf("parent%d\n", index);
			}
			lockf(1, 0, 0); // 解锁
		}
	}
	return EXIT_SUCCESS;
}

/*本实验所涉及的的系统调用lockf（files,function,size),
用作锁定文件的某些段或者整个文件。本函数的头文件为include<unistd.h>
其中file为文件描述符，function是锁定和解锁：1表示锁定，0表示解锁；
size是锁定或者解锁的字节数，为0，表示从文件的当前位置到文件尾。*/
