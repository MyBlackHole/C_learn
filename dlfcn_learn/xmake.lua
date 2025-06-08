local dir_path = path.relative(os.curdir(), os.projectdir())

target("add")
    set_kind("shared")
    add_files("add.c")
    add_cflags("-fPIC", "-g")


-- 遍历获取文件
-- 构建目标
target(dir_path)
    set_kind("binary")
    add_files("*.c")
