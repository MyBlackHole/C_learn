/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DATE_H_RPCGEN
#define _DATE_H_RPCGEN

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DATE_PROG 0x20000002
#define DATE_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define GET_DATE 1
extern long *get_date_1(void *, CLIENT *);
extern long *get_date_1_svc(void *, struct svc_req *);
extern int date_prog_1_freeresult(SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GET_DATE 1
extern long *get_date_1();
extern long *get_date_1_svc();
extern int date_prog_1_freeresult();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DATE_H_RPCGEN */
