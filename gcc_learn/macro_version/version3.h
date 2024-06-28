#define LINUX_VERSION_CODE 201472

struct socket;
int sock_create_kern(int family, int type, int proto, struct socket **res);
