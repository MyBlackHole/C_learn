target("sds")
    set_kind("static")
    -- add_includedirs("include", {public = true})
    add_files("sds.c", "zmalloc.c")

target("demo_config_parse_sds_test")
    set_kind("binary")
    add_files("sds_test.c")
    add_deps("sds")

target("demo_config_parse")
    set_kind("binary")
    add_files("config.c", "main.c")
    add_deps("sds")
