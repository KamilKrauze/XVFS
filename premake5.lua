workspace "XVFS"
    architecture "x64"
    configurations { "Debug", "Release" }
    targetdir "build/%{cfg.buildcfg}"

project "XVFS"
    targetname "%{prj.name}"
    kind "StaticLib"
    location "src"
    language "C++"
    files { 
        "**.c",
        "**.h", 
        "**.cpp",
        "**.hpp",
    }

    includedirs { "include" }

    -- Windows system
    filter "system:windows"
        system "windows"
        cppdialect "C++17"
        systemversion "latest"

    -- Linux system
    filter "system:linux"
        system "linux"
        cppdialect "gnu++17"