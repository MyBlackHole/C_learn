local dir_path = path.relative(os.curdir(), os.projectdir())

add_requires("pahomqttc")

target(dir_path)
    set_kind("binary")
    add_files("**.c")
    add_packages("pahomqttc")
    -- paru -S paho-mqtt-c
    add_links("paho-mqtt3c")
