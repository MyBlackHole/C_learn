-- add_requires("linux-headers", {configs = {driver_modules = true}})
set_values("linux.driver.linux-headers", "/lib/modules/6.9.3-arch1-1/build")
-- option("linux-headers", {showmenu = true, description = "Set linux-headers path."})

target("str_demo")
    add_rules("platform.linux.driver")
    add_files("ioctl_test.c")
    add_packages("linux-headers")
    set_license("GPL-2.0")


target("str_demo_test")
    add_files("main.c")
