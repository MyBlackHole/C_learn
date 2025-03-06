target("iot_433")
    set_kind("shared")
    add_files("iot_433.c")

target("iot_433_test")
    set_kind("binary")
    add_files("iot_433_test.c")
    add_deps("iot_433")

target("iot_server")
    set_kind("binary")
    add_files("iot_server.c")
    add_deps("iot_433")

