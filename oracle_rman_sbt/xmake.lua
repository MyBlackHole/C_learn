local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
target(dir_path)
    set_kind("shared")
    add_files("sbt.c")