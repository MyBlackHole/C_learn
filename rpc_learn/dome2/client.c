#include <stdlib.h>
#include "square.h" //由rpcgen产生的square.h

int main(int argc, char **argv)
{
	//声明客户句柄
	CLIENT *cl;
	square_in in;
	square_out *outp;

	if (argc != 3) {
		printf("usage: client <hostname> <integer-value>");
		exit(EXIT_FAILURE);
	}
	//获取客户句柄
	cl = clnt_create(argv[1], SQUARE_PROG, SQUARE_VERS, "tcp");

	//调用远程过程并输出结果
	in.arg1 = atol(argv[2]);
	if ((outp = squareproc_1(&in, cl)) == NULL) {
		printf("%s", clnt_sperror(cl, argv[1]));
		exit(EXIT_FAILURE);
	}

	printf("result: %ld\n", outp->res1);
	exit(0);
}
