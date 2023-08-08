target("sys_stat_learn/mkfifo_test", function()
    set_kind("binary")
    add_files("sys_stat_learn/mkfifo_test.c")
end)

target("sys_stat_learn/namepipe/client", function()
    set_kind("binary")
    add_files("sys_stat_learn/namepipe/client.c")
end)

target("sys_stat_learn/namepipe/server", function()
    set_kind("binary")
    add_files("sys_stat_learn/namepipe/server.c")
end)
