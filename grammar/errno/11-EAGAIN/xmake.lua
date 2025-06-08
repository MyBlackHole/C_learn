-- 构建目标
target("errno_11_client")
    set_kind("binary")
    add_files("client.c")


target("errno_11_server")
    set_kind("binary")
    add_files("server.c")
