-- -- 当前目录路径
-- print(os.curdir())
-- -- 目录名
-- print(path.filename(os.curdir()))

-- 获取相对根路径
local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)

target("no_namespace", function()
    set_kind("binary")
    add_files("no_namespace.c")
end)

target("container", function()
    set_kind("binary")
    add_files("container.c")
end)
