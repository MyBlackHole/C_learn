target("bplustree")
    set_kind("static")
    -- add_includedirs("include", {public = true})
    add_files("bplustree.c")

target("demo_bplustree_demo")
    set_kind("binary")
    add_files("bplustree_demo.c")
    add_deps("bplustree")

target("demo_bplustree_coverage")
    set_kind("binary")
    add_files("bplustree_coverage.c")
    add_deps("bplustree")
