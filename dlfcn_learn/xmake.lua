local dir_path = path.relative(os.curdir(), os.projectdir())

target("add", function()
    set_kind("shared")
    add_files("add.c")
    add_cflags("-fPIC", "-g", "-Wall")
end)


-- 遍历获取文件
-- 构建目标
target(dir_path, function()
    set_kind("binary")
    for _, file_path in ipairs(os.files(os.curdir() .. "/*.c")) do
        add_files(file_path)
    end
end)
