local dir_path = path.relative(os.curdir(), os.projectdir())

set_targetdir("$(buildir)/$(arch)/$(plat)/$(mode)/" .. dir_path)

target("munit_main", function()
    set_kind("binary")
    add_files("munit_main.c")
    add_deps("libmunit")
end)

target("libmunit", function()
    set_kind("shared")
    add_files("munit.c")
end)
