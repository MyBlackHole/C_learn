local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path)
    set_kind("binary")
    add_files("*.c")
    -- add_packages("tbox")
    add_links("curl", "ssh2", "z", "crypto", "ssl")


    -- add_linkdirs("/run/media/black/Data/lib/curl/7_35_0/lib/")
    -- add_includedirs("/run/media/black/Data/lib/curl/7_35_0/include/")

    -- add_linkdirs("/run/media/black/Data/lib/libssh2/master/lib")
    -- add_includedirs("/run/media/black/Data/lib/libssh2/master/include/")
    -- -lssh2 -lz
