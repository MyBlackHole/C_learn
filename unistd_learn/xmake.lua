local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path)
    add_defines("_GNU_SOURCE=1")
    set_kind("binary")
    add_files("*.c")
    add_links("crypt")
