local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path)
    set_kind("binary")
    add_rules("lex", "yacc")
    -- add_files("*.c")
    add_files("*.l", "*.y")
    -- add_links("yajl")
