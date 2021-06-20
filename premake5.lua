workspace "Gemstone"
    architecture "x86_64"
    startproject "Sapphire"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Gemstone"
    location "Gemstone"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GS_PLATFORM_WINDOWS",
            "GS_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sapphire")
        }

    filter "configurations:Debug"
        defines "GS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GS_DIST"
        optimize "On"


project "Sapphire"
    location "Sapphire"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Gemstone/vendor/spdlog/include",
        "Gemstone/src"
    }

    links
    {
        "Gemstone"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "GS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GS_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GS_DIST"
        optimize "On"