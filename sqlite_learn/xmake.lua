add_requires("sqlite3", {system = false, configs = {static = true}, debug = is_mode("debug")})

local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
target(dir_path)
    set_kind("binary")
    add_files("*.c")
    add_packages("sqlite3")
    add_ldflags("-static")

