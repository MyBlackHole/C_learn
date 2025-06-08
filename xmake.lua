set_warnings("all", "error")
set_languages("c99")

-- add_cxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing")
-- add_mxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing")

add_rules("mode.release", "mode.debug")
add_defines("_GNU_SOURCE=1")

-- -- 设置依赖包目录
-- add_packagedirs("packages")

-- 递归遍历获取所有层级子目录
for _, dir in ipairs(os.dirs(os.curdir() .. "/**")) do
-- -- 递归遍历获取子目录
-- for _, dir in ipairs(os.dirs(os.curdir() .. "/*")) do
    local xmake_path = path.join(dir, "xmake.lua")
    -- 判断是否存在 xmake.lua
    if os.exists(xmake_path) then
        -- 相对路径
        local dir_path = path.relative(dir, os.projectdir())
        -- 导入所有子项目
        includes(dir_path)
    end
    -- if string.find(dir_name, "learn") then
    --     includes(dir_name)
    --     -- print(dir_name)
    -- end
end

-- includes("@builtin/xpack")
-- xpack("c_learn")
--     set_description("A cross-platform build utility based on Lua.")
--     set_formats("rpm")
--     add_sourcefiles("unistd_learn/xmake.lua")
--     add_targets("unistd_learn")
