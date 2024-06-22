target("sys_stat_learn_namepipe_client")
    set_kind("binary")
    add_files("client.c")

target("sys_stat_learn_namepipe_server")
    set_kind("binary")
    add_files("server.c")
