local dir_path = path.relative(os.curdir(), os.projectdir())

add_requires("libfuse", {system = false, configs = {static = true}, debug = is_mode("debug")})
-- 遍历获取文件
-- 构建目标
target(dir_path)
    set_kind("binary")
    add_files("*.c")
    add_packages("libfuse")
    add_cxflags("-D_FILE_OFFSET_BITS=64")
    set_license("GPL-2.0")
