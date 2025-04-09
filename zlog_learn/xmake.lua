local dir_path = path.relative(os.curdir(), os.projectdir())

add_requires("zlog", {system = false, configs = {static = true}, debug = is_mode("debug")})

-- 遍历获取文件
-- 构建目标
target(dir_path)
    set_kind("binary")
    add_files("*.c")
    add_packages("zlog")
    add_ldflags("-static")
