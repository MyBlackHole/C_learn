#include <stdio.h>
#include <uv.h>

extern uv_loop_t *loop;
uv_process_t child_req;
uv_process_options_t options;

int demo_detach_main()
{
	loop = uv_default_loop();

	char *args[3];
	args[0] = "sleep";
	args[1] = "100";
	args[2] = NULL;

	options.exit_cb = NULL;
	options.file = "sleep";
	options.args = args;
	// 启动守护进程
	options.flags = UV_PROCESS_DETACHED;

	int ret;
	if ((ret = uv_spawn(loop, &child_req, &options))) {
		fprintf(stderr, "%s\n", uv_strerror(ret));
		return 1;
	}
	fprintf(stderr, "Launched sleep with PID %d\n", child_req.pid);
	// 解除监听, 使程序退出
	uv_unref((uv_handle_t *)&child_req);

	return uv_run(loop, UV_RUN_DEFAULT);
}
