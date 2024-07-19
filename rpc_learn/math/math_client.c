#include <stdio.h>
#include <stdlib.h>

#include "xdr_math.h"

void usage(char *name)
{
	printf("Usage: %s hostname/IPaddr\n", name);
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		usage(argv[0]);
	}
	printf("choose the operation:\n \t 0---ADD\t 1---SUB\t 2---MUL\t 3---DIV\n");
	char mode;
	scanf("%c", &mode);
	struct MATH math;
	switch (mode) {
	case '0':
		math.op = ADD;
		break;
	case '1':
		math.op = SUB;
		break;
	case '2':
		math.op = MUL;
		break;
	case '3':
		math.op = DIV;
		break;
	default:
		printf("error :operation\n");
		exit(1);
	}
	printf("Input the first second number:\n");
	scanf("%f %f", &math.arg1, &math.arg2);

	CLIENT *client = clnt_create(argv[1], MATH_PROG, MATH_VER, "tcp");
	// CLIENT * client = clnt_create(argv[1], MATH_PROG, MATH_VER, "udp");
	if (client == NULL) {
		printf("error :clnt_create\n");
		exit(1);
	}

	struct timeval timeout;
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;

	enum clnt_stat stat = clnt_call(client, MATH_PROC, (xdrproc_t)xdr_math,
					(char *)&math, (xdrproc_t)xdr_math,
					(char *)&math, timeout);
	if (stat != RPC_SUCCESS) {
		clnt_perror(client, "Call Failed");
		exit(1);
	}
	printf("The Result is %f .\n", math.result);
	clnt_destroy(client);
	return 0;
}
