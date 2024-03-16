local dir_path = path.relative(os.curdir(), os.projectdir())

target("libmunit")
    set_kind("shared")
    add_files("munit.c")

target(dir_path)
    set_kind("binary")
    add_files("munit_main.c")
    add_deps("libmunit")
    add_links("mysqlclient")

