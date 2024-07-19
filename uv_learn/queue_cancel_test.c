#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <uv.h>

#define FIB_UNTIL 25
extern uv_loop_t *loop;
uv_work_t fib_reqs[FIB_UNTIL];

long fib_(long data)
{
	if (data == 0 || data == 1) {
		return 1;
	} else {
		return fib_(data - 1) + fib_(data - 2);
	}
}

void fib(uv_work_t *req)
{
	int data = *(int *)req->data;
	if (random() % 2) {
		sleep(1);
	} else {
		sleep(3);
	}
	long fib = fib_(data);
	fprintf(stderr, "%dth fibonacci is %lu\n", data, fib);
}

void after_fib(uv_work_t *req, int status)
{
	if (status == UV_ECANCELED) {
		fprintf(stderr, "Calculation of %d cancelled.\n",
			*(int *)req->data);
	}
}

void signal_handler(uv_signal_t *req, int signum)
{
	printf("Signal received!\n");
	int index;
	for (index = 0; index < FIB_UNTIL; index++) {
		uv_cancel((uv_req_t *)&fib_reqs[index]);
	}
	uv_signal_stop(req);
}

int demo_queue_cancel_main()
{
	loop = uv_default_loop();

	int data[FIB_UNTIL];
	int index;
	for (index = 0; index < FIB_UNTIL; index++) {
		data[index] = index;
		fib_reqs[index].data = (void *)&data[index];
		uv_queue_work(loop, &fib_reqs[index], fib, after_fib);
	}

	uv_signal_t sig;
	uv_signal_init(loop, &sig);
	uv_signal_start(&sig, signal_handler, SIGINT);

	return uv_run(loop, UV_RUN_DEFAULT);
}
