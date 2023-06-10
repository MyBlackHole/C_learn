```c
#include<rpc/xdr.h>
#include<rpc/types.h>
bool_t xdr_int(XDR *xdrs, int *ip);     //整数
bool_t xdr_u_int(XDR *xdrs, unsigned *up);    //无符号整数
bool_t xdr_short(XDR *xdrs, short *sp);    //短整型
bool_t xdr_u_short(XDR *xdrs, unsigned short *usp);  //无符号短整型
bool_t xdr_long(XDR *xdrs, long *lp);       //长整型
bool_t xdr_u_long(XDR *xdrs, unsigned long *ulp);   //无符号长整型
bool_t xdr_bool(XDR *xdrs, bool_t *bp);     //布尔型
bool_t xdr_enum(XDR *xdrs, enum_t *ep);   //枚举
bool_t xdr_float(XDR *xdrs, float *fp);       //单精度浮点型
bool_t xdr_double(XDR *xdrs, double *dp);   //双精度浮点型
bool_t xdr_char(XDR *xdrs, char *cp);        //字符型
bool_t xdr_string(XDR *xdrs, char **sp, unsigned int maxsize);   //字符串型
bool_t xdr_bytes(XDR *xdrs, char **sp, unsigned int *sizep,
                        unsigned int maxsize);    //字节流
bool_t xdr_vector(XDR *xdrs, char *arrp, unsigned int size,
                         unsigned int elsize, xdrproc_t elproc);  //定长数组
bool_t xdr_array(XDR *xdrs, char **arrp, unsigned int *sizep,
                        unsigned int maxsize, unsigned int elsize,
                        xdrproc_t elproc);  //变长数组
```
