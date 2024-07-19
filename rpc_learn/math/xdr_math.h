#include <stdbool.h>

#include <rpc/clnt.h>
#include <rpc/svc.h>
#include <rpc/types.h>
#include <rpc/xdr.h>

struct MATH {
	int op;
	float arg1;
	float arg2;
	float result;
};

bool xdr_math(XDR *xdrsp, struct MATH *resp)
{
	if (!xdr_int(xdrsp, &resp->op)) {
		return false;
	}
	if (!xdr_float(xdrsp, &resp->arg1)) {
		return false;
	}
	if (!xdr_float(xdrsp, &resp->arg2)) {
		return false;
	}
	if (!xdr_float(xdrsp, &resp->result)) {
		return false;
	}
	return TRUE;
}

#define MATH_PROG ((unsigned long)0x20000001)
#define MATH_VER ((unsigned long)0x1)
#define MATH_PROC ((unsigned long)0x1)
#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
