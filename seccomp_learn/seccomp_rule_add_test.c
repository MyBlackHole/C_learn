#include <seccomp.h>
#include <unistd.h>
#include <syscall.h>

int demo_seccomp_rule_add_main()
{
	scmp_filter_ctx ctx;
	// 初始化过滤器上下文，默认允许所有系统调用
	ctx = seccomp_init(SCMP_ACT_ALLOW);

	// 添加规则，禁止 execve 系统调用
	seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);

	// 加载 seccomp 过滤器
	seccomp_load(ctx);

	// 尝试执行 execve 系统调用（将被禁止）
	char *argv[] = { "/bin/sh", NULL };
	// syscall(SYS_execve, "/bin/sh", argv, NULL);
	execve("/bin/sh", argv, NULL);

	seccomp_release(ctx); // 释放 seccomp 过滤器上下文
	return 0;
}

// 编译运行：
// ❯ xmake run seccomp_learn seccomp_rule_add
// error: execv(/run/media/black/Data/Documents/c/build/linux/x86_64/debug/seccomp_learn seccomp_rule_add) failed(-1)
