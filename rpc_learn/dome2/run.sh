# https://blog.csdn.net/weixin_50866517/article/details/127147265
# 前提 port 111
systemctl start rpcbind.socket

rpcgen -C square.x
cc -c client.c -o client.o -g -I/usr/include/tirpc
cc -c square_clnt.c -o square_clnt.o -g -I/usr/include/tirpc
cc -c square_xdr.c -o square_xdr.o -g -I/usr/include/tirpc
cc -o client client.o square_clnt.o square_xdr.o  -g -I/usr/include/tirpc -lnsl -ltirpc

cc -c server.c -o server.o -g -I/usr/include/tirpc
cc -c square_svc.c -o square_svc.o -g -I/usr/include/tirpc
cc -o server server.o square_svc.o square_xdr.o  -g -I/usr/include/tirpc -lnsl -ltirpc

./server

rpcinfo
 ..................................................................
 ..................................................................
 ..................................................................
 824377344    1    udp       0.0.0.0.234.219        -          1000
 824377344    1    tcp       0.0.0.0.231.80         -          1000

./client 127.0.0.1 1
result: 1


