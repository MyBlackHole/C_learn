-- 构建目标
target("errno_32_client")
    set_kind("binary")
    add_files("client.c")


target("errno_32_server")
    set_kind("binary")
    add_files("server.c")

target("errno_32_demo1")
    set_kind("binary")
    add_files("demo1.c")

target("errno_32_demo2")
    set_kind("binary")
    add_files("demo2.c")
