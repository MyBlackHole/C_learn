-- 构建目标
target("sigpipe_test_client")
    set_kind("binary")
    add_files("client.c")


target("sigpipe_test_server")
    set_kind("binary")
    add_files("server.c")
