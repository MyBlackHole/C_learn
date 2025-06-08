#include <stdio.h>
#include "macor.h"

int main()
{
	int family, type, proto;
#if SIMPLEFS_AT_LEAST(4, 19, 0)
	struct net *net
#endif

#if SIMPLEFS_AT_LEAST(4, 19, 0)
		sock_create_kern(net, family, type, proto, NULL);
#else
	sock_create_kern(family, type, proto, NULL);
#endif
}
