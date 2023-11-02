local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_objectdir("$(buildir)/.objs/$(arch)/$(plat)/$(mode)/" .. dir_path)
set_dependir("$(buildir)/.deps/$(arch)/$(plat)/$(mode)/" .. dir_path)

target("client", function()
    set_kind("binary")
    add_files("client.c")
end)

target("server", function()
    set_kind("binary")
    add_files("server.c")
end)
