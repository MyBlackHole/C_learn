local dir_path = path.relative(os.curdir(), os.projectdir())

-- 使用非系统的protobuf-c库，并设置为静态库
add_requires("protobuf-c", {system = false, configs = {static = true}, debug = is_mode("debug")})
-- add_requires("protobuf-c")

target(dir_path)
    set_kind("binary")
    add_packages("protobuf-c")
    add_rules("protobuf.c")
    add_files("*.c")
    add_files("*.proto", {proto_rootdir = dir_path})
    add_files("subdir/*.proto", {proto_rootdir = dir_path})

