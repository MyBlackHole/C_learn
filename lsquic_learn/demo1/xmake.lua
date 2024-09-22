local dir_path = path.relative(os.curdir(), os.projectdir())


add_requires("libev", {system = false, configs = {static = true}, debug = is_mode("debug")})
-- add_requires("boringssl 9fc1c33e9c21439ce5f87855a6591a9324e569fd", {system = false, configs = {static = true}, debug = is_mode("debug")})
-- add_requires("lsquic master", {system = false, configs = {static = true}, debug = is_mode("debug")})
add_requires("lsquic", {system = false, configs = {static = true}, debug = is_mode("debug")})

-- 当前版本不对, boringssl 需要 9fc1c33e9c21439ce5f87855a6591a9324e569fd

target("lsquic_learn_demo1_tut")
    set_kind("binary")
    add_files("tut.c")
    add_packages("libev", "lsquic")
    -- add_packages("libev", "boringssl", "lsquic")

target("lsquic_learn_demo1_h3cli")
    set_kind("binary")
    add_files("h3cli.c")
    add_packages("libev", "lsquic")
    -- add_packages("libev", "boringssl", "lsquic")
