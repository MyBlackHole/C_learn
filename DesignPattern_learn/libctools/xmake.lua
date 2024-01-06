-- local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
target("libctools", function()
    set_kind("static")
    add_includedirs("include")
    for _, file_path in ipairs(os.files(os.curdir() .. "/**.c")) do
        add_files(file_path)
    end
end)
