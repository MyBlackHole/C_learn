local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
for _, file_path in ipairs(os.files(os.curdir() .. "/*test.c")) do
    basename = path.basename(file_path)
    filename = path.filename(file_path)
    target(basename)
        set_kind("binary")
        add_files(filename)
end
