local dir_path = path.relative(os.curdir(), os.projectdir())

target(dir_path)
    set_kind("binary")
    add_files("**.c")
    add_linkdirs("/media/black/Data/lib/paho.mqtt.c/master/lib/")
    add_includedirs("/media/black/Data/lib/paho.mqtt.c/master/include/")
    add_links("paho-mqtt3c")
