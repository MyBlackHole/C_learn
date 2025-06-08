target("demo_thread_pool_adlist")
    set_kind("static")
    add_files("adlist.c", "zmalloc.c", "bio.c")

target("demo_thread_pool_threadPoll_Main")
    set_kind("binary")
    add_files("threadPoll_Main.c")
    add_deps("demo_thread_pool_adlist")
