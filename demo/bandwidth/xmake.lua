target("demo_bandwidth_lib")
    set_kind("static")
    add_defines("__USE_GNU")
    add_files("bandwidth.c")


-- target("demo_bandwidth_lib")
--     add_defines("__USE_GNU")
--     set_kind("binary")
--     add_files("*.c")
