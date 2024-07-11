-- 构建目标
target("errno_32_client")
    set_kind("binary")
    add_files("client.c")


target("errno_32_server")
    set_kind("binary")
    add_files("server.c")
