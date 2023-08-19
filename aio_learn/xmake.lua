local dir_path = path.relative(os.curdir(), os.projectdir())

-- 遍历获取文件
-- 构建目标
target(dir_path, function()
    set_kind("binary")
    for _, file_path in ipairs(os.files(os.curdir() .. "/*.c")) do
        add_files(file_path)
    end

    -- add_files("aio_learn.c")
    -- add_files("aio_read.c")
    -- add_files("aio_write.c")
    -- add_files("lio_listio.c")
    -- add_files("aio_suspend.c")
    -- add_files("demo.c")
    add_links("aio")
end)

-- for _, file_path in ipairs(os.files(os.curdir() .. "/*.c")) do
--     basename = path.basename(file_path)
--     filename = path.filename(file_path)

--     target(basename, function()
--         set_kind("binary")
--         add_files(filename)
--         add_links("aio")
--     end)
-- end
