local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_objectdir("$(buildir)/.objs/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_dependir("$(buildir)/.deps/$(arch)/$(plat)/$(mode)/" .. dir_path)

-- 遍历获取文件
-- 构建目标
for _, file_path in ipairs(os.files(os.curdir() .. "/*.c")) do
    basename = path.basename(file_path)
    filename = path.filename(file_path)

    target(basename, function()
        set_kind("binary")
        add_files(filename)
        add_linkdirs("/media/black/Data/lib/paho.mqtt.c/master/lib/")
        add_includedirs("/media/black/Data/lib/paho.mqtt.c/master/include/")
        add_links("paho-mqtt3c")
    end)
end
