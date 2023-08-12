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

target("unistd_learn/setsid_test", function()
    set_kind("binary")
    add_files("unistd_learn/setsid_test.c")
end)

target("unistd_learn/setpgid_test", function()
    set_kind("binary")
    add_files("unistd_learn/setpgid_test.c")
end)

target("grammar_learn/struct1_test", function()
    set_kind("binary")
    add_files("grammar_learn/struct1_test.c")
end)

target("mysql_learn/demo", function()
    set_kind("binary")
    add_files("mysql_learn/demo.c")
    -- 依赖 libmysqlclient-dev
    add_links("mysqlclient")
end)
