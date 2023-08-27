-- function yacc()
--     os.execv("/usr/bin/yacc -dv calc.y")
--     os.execv("/usr/bin/lex calc.y")
-- end

local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path, function()
    set_kind("binary")
    for _, file_path in ipairs(os.files(os.curdir() .. "/*.c")) do
        add_files(file_path)
        add_links("yajl")
    end
end)
