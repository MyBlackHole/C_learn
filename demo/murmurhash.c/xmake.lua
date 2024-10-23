target("murmurhash")
    set_kind("static")
    -- add_includedirs("include", {public = true})
    add_files("murmurhash.c")

target("demo_murmurhash_c_test")
    set_kind("binary")
    add_files("test.c")
    add_deps("murmurhash")

target("demo_murmurhash_c_test1")
    set_kind("binary")
    add_files("test1.c")
    add_deps("murmurhash")

target("demo_murmurhash_c")
    set_kind("binary")
    add_files("main.c")
    add_deps("murmurhash")
