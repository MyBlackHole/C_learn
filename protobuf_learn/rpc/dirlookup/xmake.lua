-- 使用非系统的protobuf-c库，并设置为静态库
add_requires("protobuf-c", { system = false, configs = { static = true }, debug = is_mode("debug") })
-- add_requires("protobuf-c")

package("protobuf-c-rpc")

    set_sourcedir("/run/media/black/Data/Documents/github/c/protobuf-c-rpc")

    -- 依赖protobuf-c库
    add_deps("protobuf-c")

    on_install(function(package)
        local configs = {}
        table.insert(configs, "--enable-shared=" .. (package:config("shared") and "yes" or "no"))
        table.insert(configs, "--enable-static=" .. (package:config("shared") and "no" or "yes"))
        if package:debug() then
            table.insert(configs, "--enable-debug")
        end
        table.insert(configs, "CFLAGS=-g -O0")
        import("package.tools.autoconf").install(package, configs)
    end)

    on_test(function(package)
        assert(
            package:has_cfuncs(
                "protobuf_c_rpc_client_set_rpc_protocol",
                {
                    includes = "protobuf-c-rpc/protobuf-c-rpc.h",
                    "protobuf-c-rpc/protobuf-c-rpc-dispatch.h",
                    "protobuf-c-rpc/protobuf-c-rpc-data-buffer.h",
                }
            )
        )
    end)

package_end()

add_requires("protobuf-c-rpc", { system = false, configs = { static = true }, debug = is_mode("debug") })

target("dirlookup_rpc_server")
    set_kind("binary")
    add_packages("protobuf-c")
    add_packages("protobuf-c-rpc")
    -- add_links("protobuf-c-rpc")
    add_rules("protobuf.c")
    add_files("example-server.c")
    add_files("*.proto", { proto_rootdir = "protobuf_learn/rpc/dirlookup" })

target("dirlookup_rpc_client")
    set_kind("binary")
    add_packages("protobuf-c")
    add_packages("protobuf-c-rpc")
    -- add_links("protobuf-c-rpc")
    add_rules("protobuf.c")
    add_files("example-client.c")
    add_files("*.proto", { proto_rootdir = "protobuf_learn/rpc/dirlookup" })
