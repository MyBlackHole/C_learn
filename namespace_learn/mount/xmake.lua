-- 获取相对根路径
local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)

target("unshare", function()
    set_kind("binary")
    add_files("unshare.c")
end)
