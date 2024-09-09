local dir_path = path.relative(os.curdir(), os.projectdir())


add_requires("libev", {system = false, configs = {static = true}, debug = is_mode("debug")})
add_requires("lsquic", {system = false, configs = {static = true}, debug = is_mode("debug")})
add_requires("boringssl", {system = false, configs = {static = true}, debug = is_mode("debug")})

target("lsquic_learn_demo1_tut")
    set_kind("binary")
    add_files("tut.c")
    add_packages("libev", "lsquic", "boringssl")

target("lsquic_learn_demo1_h3cli")
    set_kind("binary")
    add_files("h3cli.c")
    add_packages("libev", "lsquic", "boringssl")
