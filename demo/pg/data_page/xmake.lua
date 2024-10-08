target("page_check_tools")
    set_kind("binary")
    -- 静态连接
	add_ldflags("-static")
    add_files("*.c")
