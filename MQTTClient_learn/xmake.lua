local dir_path = path.relative(os.curdir(), os.projectdir())

-- add_requires("mqtt3c")

target(dir_path)
    set_kind("binary")
    add_files("**.c")
    -- add_linkdirs("/media/black/Data/lib/paho.mqtt.c/master/lib/")
    -- add_includedirs("/media/black/Data/lib/paho.mqtt.c/master/include/")
    -- yay -S paho-mqtt-c
    -- paru -S paho-mqtt-c
    add_links("paho-mqtt3c")
