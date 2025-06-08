#include "date.h"

void date_prog_1(char *host)
{
	CLIENT *clnt;
	long *result_1;
	char *get_date_1_arg;

	clnt = clnt_create(host, DATE_PROG, DATE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}

	result_1 = get_date_1((void *)&get_date_1_arg, clnt);
	if (result_1 == (long *)NULL) {
		clnt_perror(clnt, "call failed");
		exit(1);
	}
	printf("time on host %s: %ld\n", host, *result_1); // 添加输出

	clnt_destroy(clnt);
}

int main(int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}

	host = argv[1];
	date_prog_1(host);
	exit(0);
}
