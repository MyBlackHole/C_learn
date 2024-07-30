local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
target(dir_path)
    add_defines("__USE_GNU")
    set_kind("binary")
    add_files("*.c")
