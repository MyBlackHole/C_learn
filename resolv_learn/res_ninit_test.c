#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <netinet/in.h>
#include <resolv.h>
#include <stdlib.h>

int main()
{
    res_state res = malloc(sizeof(*res));
    res_ninit(res);
    int i = 0;
    /* res->nscount存储了域名服务器的个数 */
    for (i = 0; i < res->nscount; i++)
    {
        /* 域名服务器的地址 */
        struct sockaddr_in addr = res->nsaddr_list[i];
        char *strAddr = inet_ntoa(addr.sin_addr);
        printf("P: %p, IP: %s, PORT: %d\n", strAddr, strAddr,
               ntohs(addr.sin_port));
    }
    // exit(0);
    int class = C_IN;
    int type = T_A;
    unsigned char answer[256] = "";
    /* answer中为域名解析的结果 */
    int n =
        res_nquery(res, "www.baidu.com", class, type, answer, sizeof(answer));
    res_nclose(res);
    for (int i = 0; i < n; i++)
    {
        printf("%02x", answer[i]);
    }
    exit(0);
}
