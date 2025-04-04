target("net_tcp_time_wait_client")
    set_kind("binary")
    add_files("client.c")


target("net_tcp_time_wait_server")
    set_kind("binary")
    add_files("server.c")
