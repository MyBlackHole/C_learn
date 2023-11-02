-- 获取相对根路径
local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_objectdir("$(buildir)/.objs/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_dependir("$(buildir)/.deps/$(arch)/$(plat)/$(mode)/" .. dir_path)

target("uts", function()
    set_kind("binary")
    add_files("uts.c")
end)
