target("sys_mman_learn_mutex_sm_client")
    set_kind("binary")
    add_files("sm_client.c")

target("sys_mman_learn_mutex_sm_server")
    set_kind("binary")
    add_files("sm_server.c")
