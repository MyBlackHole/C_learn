# close

关闭文件描述符, 根据不同 file_operations 作不同操作
对于 socket 在 fork(clone 可以配置是否共享父进程 ipc net 等...) 之前建立的 socket 父子进程都有引用(引用计数2)
当子进程 close(引用计数变1)关闭本进程的socket id,但链接还是开着的，用这个socket id的其它进程还能用这个链接，能读或写这个socket id
想直接关闭所有引用使用 [[../sys_socket_learn/shutdown]]
