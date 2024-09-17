set_xmakever("2.9.4")
set_warnings("all", "error")
set_languages("c99")
add_cxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing")
add_mxflags("-Wno-error=deprecated-declarations", "-fno-strict-aliasing")

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

includes("@builtin/xpack")
xpack("c_learn")
    set_description("A cross-platform build utility based on Lua.")
    set_license("Apache-2.0")
    set_formats("rpm")
    add_sourcefiles("unistd_learn/xmake.lua")
    add_targets("unistd_learn")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--
