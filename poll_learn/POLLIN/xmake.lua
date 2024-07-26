target("pool_POLLIN_client")
    set_kind("binary")
    add_files("client.c")


target("pool_POLLIN_server")
    set_kind("binary")
    add_files("server.c")
