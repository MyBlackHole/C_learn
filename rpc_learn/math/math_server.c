#include <stdio.h>
#include <stdlib.h>

#include "xdr_math.h"

static void mathprog(struct svc_req *rqstp, SVCXPRT *transp)
{
	switch (rqstp->rq_proc) {
	case NULLPROC:
		svc_sendreply(transp, (xdrproc_t)xdr_void, NULL);
		return;
	case MATH_PROC:
		break;
	default:
		svcerr_noproc(transp);
		return;
	}

	struct MATH math;
	memset((char *)&math, 0, sizeof(math));
	if (!svc_getargs(transp, (xdrproc_t)xdr_math, (caddr_t)&math)) {
		svcerr_decode(transp);
		return;
	}
	switch (math.op) {
	case ADD:
		math.result = math.arg1 + math.arg2;
		break;
	case SUB:
		math.result = math.arg1 - math.arg2;
		break;
	case MUL:
		math.result = math.arg1 * math.arg2;
		break;
	case DIV:
		math.result = math.arg1 / math.arg2;
		break;
	default:
		break;
	}
	if (!svc_sendreply(transp, (xdrproc_t)xdr_math, (caddr_t)&math)) {
		printf("error:unable to send reply\n");
		exit(1);
	}
	if (!svc_freeargs(transp, (xdrproc_t)xdr_math, (caddr_t)&math)) {
		printf("error:unable to free args\n");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	SVCXPRT *transpu = svcudp_create(RPC_ANYSOCK);
	if (transpu == NULL) {
		printf("error: cannot create udp service.\n");
		exit(1);
	}
	if (!svc_register(transpu, MATH_PROG, MATH_VER, mathprog,
			  IPPROTO_UDP)) {
		printf("error: cannot register (MATH_PROG udp) .\n");
		exit(1);
	}

	SVCXPRT *transpt = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transpt == NULL) {
		printf("error: cannot create tcp service.\n");
		exit(1);
	}
	if (!svc_register(transpt, MATH_PROG, MATH_VER, mathprog,
			  IPPROTO_TCP)) {
		printf("error: cannot register (ADDPROG tdp) .\n");
		exit(1);
	}
	svc_run();
	printf("error: scv_run returned");
	exit(1);
}
