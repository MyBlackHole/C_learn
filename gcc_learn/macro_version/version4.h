#define LINUX_VERSION_CODE 267263

struct socket;
struct net;
int sock_create_kern(struct net *net, int family, int type, int proto,
		     struct socket **res);
