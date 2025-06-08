local dir_path = path.relative(os.curdir(), os.projectdir())

add_requires("inih", "tbox")

-- 遍历获取文件
-- 构建目标
target(dir_path)
    set_kind("binary")
    add_files("*.c")
    add_packages("tbox", "inih")
    add_links("inih")
