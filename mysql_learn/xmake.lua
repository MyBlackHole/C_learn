local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path)
    set_kind("binary")
    add_files("*.c")
    -- paru -S mariadb-clients
    add_links("mysqlclient")

