local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)

target("getspnam_", function()
    set_kind("binary")
    add_files("getspnam_.c")
    add_links("crypt")
end)

target("crypt_", function()
    set_kind("binary")
    add_files("crypt_.c")
    add_links("crypt")
end)


-- 遍历获取文件
-- 构建目标
for _, file_path in ipairs(os.files(os.curdir() .. "/*test.c")) do
    basename = path.basename(file_path)
    filename = path.filename(file_path)

    target(basename, function()
        set_kind("binary")
        add_files(filename)
    end)
end
