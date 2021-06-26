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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Gemstone/vendor/GLFW/include"
IncludeDir["Glad"] = "Gemstone/vendor/Glad/include"
IncludeDir["ImGui"] = "Gemstone/vendor/ImGui"

include "Gemstone/vendor/GLFW"  -- include a premake file in the other location
include "Gemstone/vendor/Glad"
include "Gemstone/vendor/ImGui"

project "Gemstone"
    location "Gemstone"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gspch.h"
    pchsource "%{prj.name}/src/gspch.cpp"

    files -- files included in the project
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs -- additional include directories
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links -- additional dependencies
    {
        "GLFW",         -- reference to project in the same solution
        "Glad",
        "ImGui",
        "opengl32.lib"  -- library
    }

    filter "system:windows" -- project properties
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"  -- windows SDK version

        defines
        {
            "GS_PLATFORM_WINDOWS",
            "GS_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands   -- DLL file in Engine project moves to Client project
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sapphire")
        }

    filter "configurations:Debug"
        defines
        {
            "GS_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "GS_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "GS_DIST"
        runtime "Release"
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
        "Gemstone"  -- reference to project in the same solution
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "GS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines
        {
            "GS_DEBUG",
            "GS_ENABLE_ASSERTS"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "GS_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "GS_DIST"
        runtime "Release"
        optimize "On"