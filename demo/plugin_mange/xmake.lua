target("demo_plugin_mange")
    set_kind("binary")
    add_files("main.c")
    add_links("seccomp")

target("plugin_mange_plugin_1")
    set_kind("shared")
    add_files("plugin_1.c")
    add_cflags("-fPIC", "-g")
