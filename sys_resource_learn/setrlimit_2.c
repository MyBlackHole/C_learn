#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

#define MEM_LIM 8 * 1024 * 1024 // 最大虚拟内存为8MB

int demo_setrlimit_2_main(void)
{
	struct rlimit old_limit;
	struct rlimit new_limit;
	char *p;

	// 获取当前的虚拟内存限制
	getrlimit(RLIMIT_AS, &old_limit);
	printf("旧的软限制: %lu MB\n", old_limit.rlim_cur / 1024 / 1024);
	printf("旧的硬限制: %lu MB\n", old_limit.rlim_max / 1024 / 1024);

	// 设置新的虚拟内存限制
	new_limit.rlim_cur = MEM_LIM / 2;
	new_limit.rlim_max = MEM_LIM;
	setrlimit(RLIMIT_AS, &new_limit);

	// 获取新的虚拟内存限制
	getrlimit(RLIMIT_AS, &new_limit);
	printf("新的软限制: %lu MB\n", new_limit.rlim_cur / 1024 / 1024);
	printf("新的硬限制: %lu MB\n", new_limit.rlim_max / 1024 / 1024);

	// 申请一块内存，超过限制时会触发 ENOMEM
	p = malloc(MEM_LIM * 2);
	if (p == NULL) {
		perror("malloc");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

// 编译运行：
// ❯ xmake run sys_resource_learn setrlimit_2
// 旧的软限制: 17592186044415 MB
// 旧的硬限制: 17592186044415 MB
// 新的软限制: 4 MB
// 新的硬限制: 8 MB
// malloc: Cannot allocate memory
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/sys_resource_learn setrlimit_2) failed(1)
