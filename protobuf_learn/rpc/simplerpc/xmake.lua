-- 使用非系统的protobuf-c库，并设置为静态库
add_requires("protobuf-c", {system = false, configs = {static = true}, debug = is_mode("debug")})
-- add_requires("protobuf-c")

-- target("simplerpc_rpc")
--     set_kind("binary")
--     add_packages("protobuf-c")
--     add_links("protobuf-c-rpc")
--     add_rules("protobuf.c")
--     add_files("simplerpc.c")
--     add_files("*.proto", {proto_rootdir = "protobuf_learn/rpc/simplerpc"})
--
