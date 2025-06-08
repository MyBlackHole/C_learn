-- add target
target("Status")

    -- set kind
    set_kind("shared")

    -- add the header files for installing
    add_headerfiles("**.h")

    -- add includes directory
    add_includedirs(".", {interface = true})

    -- add files
    add_files("*.c")

