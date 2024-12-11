target("sys_mman_learn_tcp_lib")
    set_kind("static")
    add_defines("_GNU_SOURCE")
    add_files("comm.c", "config.c", "bandwidth.c")

target("sys_mman_learn_tcp_client")
    set_kind("binary")
	add_ldflags("-static")
    add_files("client.c")
    add_deps("sys_mman_learn_tcp_lib")

target("sys_mman_learn_tcp_client_base")
    set_kind("binary")
    add_files("client_base.c")
	add_ldflags("-static")
    add_deps("sys_mman_learn_tcp_lib")

target("sys_mman_learn_tcp_server")
    set_kind("binary")
    add_files("server.c")
	add_ldflags("-static")
    add_deps("sys_mman_learn_tcp_lib")

target("sys_mman_learn_tcp_config_init")
    set_kind("binary")
	add_ldflags("-static")
    add_files("config_init.c")
    add_deps("sys_mman_learn_tcp_lib")
