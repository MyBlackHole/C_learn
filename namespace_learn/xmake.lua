-- -- 当前目录路径
-- print(os.curdir())
-- -- 目录名
-- print(path.filename(os.curdir()))

-- 获取相对根路径
-- local dir_path = path.relative(os.curdir(), os.projectdir())

target("container")
    set_kind("binary")
    add_files("container.c")


target("no_namespace")
    set_kind("binary")
    add_files("no_namespace.c")
