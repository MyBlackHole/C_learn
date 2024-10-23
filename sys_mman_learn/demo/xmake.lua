target("sys_mman_learn_demo_comm")
    set_kind("static")
    -- add_includedirs("include", {public = true})
    add_files("comm.c")

target("sys_mman_learn_demo_client")
    set_kind("binary")
    add_files("client.c")
    add_deps("sys_mman_learn_demo_comm")

target("sys_mman_learn_demo_server")
    set_kind("binary")
    add_files("server.c")
    add_deps("sys_mman_learn_demo_comm")
