local dir_path = path.relative(os.curdir(), os.projectdir())

add_requires("tbox", {debug = is_mode("debug")})

target(dir_path)
    set_kind("binary")
    add_files("*.c")
    add_packages("tbox")

