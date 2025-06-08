add_requires("liburing", {system = false, configs = {static = true}, debug = is_mode("debug")})

target("demo_io_uring_echo_server")
    set_kind("binary")
    add_files("io_uring_echo_server.c")
    add_packages("liburing")
    -- add_links("uring")
