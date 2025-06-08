# 

- 编译 .x 文件
```shell
rpcgen date.x 
生成三个源文件  date_clnt.c  、date.h、  date_svc.c
```
- 生成 makefile
```shell
rpcgen -Sm -o Makefile date.x
```

- 生成客户端
```shell
rpcgen -Sc -o date_client.c date.x
```

- 生成服务器端
```shell
rpcgen -Ss -o date_server.c date.x
```

- 编译
```shell
# 编译服务器端
gcc -Wall -o date_server date_clnt.c date_server.c date_svc.c
# 编译客户端
gcc -Wall -o date_client date_client.c date_clnt.c
```
