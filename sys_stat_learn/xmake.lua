local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_objectdir("$(buildir)/.objs/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_dependir("$(buildir)/.deps/$(arch)/$(plat)/$(mode)/" .. dir_path)

target("futimens_test", function()
    set_kind("binary")
    add_files("futimens_test.c")
end)

target("mkfifo_test", function()
    set_kind("binary")
    add_files("mkfifo_test.c")
end)
