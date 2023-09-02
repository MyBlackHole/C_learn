local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
target(dir_path, function()
    set_kind("binary")
    add_files("dlfcn_learn.c", "demo.c", "dlsym_test.c")
end)


target("add", function()
    set_kind("shared")
    add_files("add.c")
    add_cflags("-fPIC", "-g", "-Wall")
end)
