target("demo_base62_decode")
    set_kind("binary")
    add_files("decode.c", "base62.c")

target("demo_base62_encode")
    set_kind("binary")
    add_files("encode.c", "base62.c")
