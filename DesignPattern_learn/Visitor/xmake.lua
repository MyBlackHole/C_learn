local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path)
    set_kind("binary")
    add_defines("__USE_GNU")
    add_files("**.c")
    add_includedirs("include")
    add_deps("ctools")
