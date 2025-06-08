local dir_path = path.relative(os.curdir(), os.projectdir())

-- add_requires("raft", {debug = is_mode("debug")})

target(dir_path)
    set_kind("binary")
    add_files("*.c")
    add_includedirs(".")
    -- paru -S raft
    add_links("raft", "uv")
    -- add_packages("raft")
