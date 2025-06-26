target("net_tcp_test_data_client")
    set_kind("binary")
    add_files("client.c")


target("net_tcp_test_data_server")
    set_kind("binary")
    add_files("server.c")
