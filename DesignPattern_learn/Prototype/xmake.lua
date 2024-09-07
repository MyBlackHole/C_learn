local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path)
    add_deps("ctools")
    set_kind("binary")
    add_files("**.c")
    add_includedirs("include")
