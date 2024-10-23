target("sys_mman_learn_demo1_comm")
    set_kind("static")
    -- add_includedirs("include", {public = true})
    add_files("comm.c")

target("sys_mman_learn_demo1_client")
    set_kind("binary")
    add_files("client.c")
    add_deps("sys_mman_learn_demo1_comm")

target("sys_mman_learn_demo1_client_base")
    set_kind("binary")
    add_files("client_base.c")
    add_deps("sys_mman_learn_demo1_comm")

target("sys_mman_learn_demo1_server")
    set_kind("binary")
    add_files("server.c")
    add_deps("sys_mman_learn_demo1_comm")
