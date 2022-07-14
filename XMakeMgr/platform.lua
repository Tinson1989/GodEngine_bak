local rootPath = path.join(os.projectdir(), "Platform") --local lib_path = path.join(os.projectdir(),"dev","tools","DataReport")
local frameworkPath = path.join(os.projectdir(), "Framework")
local externalPath = path.join(os.projectdir(), "External")
-- target("memoryTest")
--     set_group("test")
--     set_kind("binary")
--     add_files(path.join(rootPath, "TestMemoryManager.cpp"))
--     add_deps("framework")
--     add_includedirs(frameworkPath)
--     add_filegroups("src", {rootdir = rootPath})

target("windows")
    set_kind("binary")
    add_files(path.join(rootPath, "Windows/*.cpp"))
    add_headerfiles(path.join(rootPath, "Windows/*.hpp"))
    add_deps("framework")
    add_includedirs(frameworkPath)
    add_filegroups("src", {rootdir = path.join(rootPath, "Windows")})
    set_group("platform")
    set_default(true)
    add_links("user32","d3d11","d3dcompiler","Gdi32","Opengl32")

    --添加glad库
    add_includedirs(path.join(externalPath, "Glad/include"))
    add_headerfiles(path.join(externalPath, "Glad/include/**.h"))
    add_files(path.join(externalPath, "Glad/src/*.c"))

    local libPath = ""
    if is_mode("debug") then
        libPath = path.join(externalPath, "Assimp/lib/assimp-vc143-mtd")
    else
        libPath = path.join(externalPath, "Assimp/lib/assimp-vc143-mt")
    end
    add_links(libPath)
    add_includedirs(path.join(externalPath, "Assimp/include"))
    add_headerfiles(path.join(externalPath, "Assimp/include/**.h"))

target("empty")
    set_kind("binary")
    add_files(path.join(rootPath, "Empty/*.cpp"))
    add_headerfiles(path.join(rootPath, "Empty/*.hpp"))
    add_deps("framework")
    add_includedirs(frameworkPath)
    add_filegroups("src", {rootdir = path.join(rootPath, "Empty")})
    set_group("platform")