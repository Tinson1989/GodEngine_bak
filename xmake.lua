add_rules("mode.debug", "mode.release", "mode.releasedbg", "mode.minsizerel")

set_project("GodEngine")
set_languages("cxx17")
if is_mode("debug") then
    set_suffixname("_d")
    add_defines("_DEBUG","WIN32")
    set_runtimes("MTd")
elseif is_mode("release") then 
    add_defines("_RELEASE")
elseif is_mode("releasedbg") then 
    add_defines("_RELEASEWITHDEBINFO")
elseif is_mode("minsizerel") then
    add_defines("_MINSIZEREL")
end

target("framework")
    set_kind("static")
    add_headerfiles("Framework/**.hpp")
    add_headerfiles("Framework/**.h")
    add_includedirs("Framework")
    add_files("Framework/**.cpp")
    

target("winshell")
    set_kind("binary")
    add_files("Platform/Windows/*.cpp")
    add_headerfiles("Platform/Windows/*.hpp")
    -- add_deps("framework")
    add_includedirs("Framework")

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
--    -- add macro defination
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

