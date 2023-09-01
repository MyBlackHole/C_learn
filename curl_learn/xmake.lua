local dir_path = path.relative(os.curdir(), os.projectdir())


-- 遍历获取文件
-- 构建目标
target(dir_path, function()
    set_kind("binary")
    for _, file_path in ipairs(os.files(os.curdir() .. "/*.c")) do
        add_files(file_path)
    end
    add_linkdirs("/media/black/Data/lib/curl/7_35_0/lib/")
    add_includedirs("/media/black/Data/lib/curl/7_35_0/include/")

    add_linkdirs("/media/black/Data/lib/libssh2/master/lib")
    add_includedirs("/media/black/Data/lib/libssh2/master/include/")
    add_links("curl", "ssh2", "z", "crypto", "ssl")
    -- -lssh2 -lz
end)
