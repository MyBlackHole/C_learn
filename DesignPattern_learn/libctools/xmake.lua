target("ctools")
    set_kind("static")
    -- public: true, 代表头文件可以被其他项目引用
    add_includedirs("include", {public = true})
    add_files("src/*.c")
    add_files("src/*.cpp")
