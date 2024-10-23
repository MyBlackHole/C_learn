
target("demo_Tinyhttpd_simpleclient")
    set_kind("binary")
    add_files("simpleclient.c")

target("demo_Tinyhttpd_httpd")
    set_kind("binary")
    add_files("httpd.c")
