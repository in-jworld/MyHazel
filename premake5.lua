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
IncludeDir["glm"] = "Gemstone/vendor/glm"

group "Dependencies"
    include "Gemstone/vendor/GLFW"  -- include a premake file in the other location
    include "Gemstone/vendor/Glad"
    include "Gemstone/vendor/ImGui"
group ""

project "Gemstone"
    location "Gemstone"
    kind "StaticLib"
    staticruntime "On"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "gspch.h"
    pchsource "%{prj.name}/src/gspch.cpp"

    files -- files included in the project
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs -- additional include directories
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links -- additional dependencies
    {
        "GLFW",         -- reference to project in the same solution
        "Glad",
        "ImGui",
        "opengl32.lib"  -- library
    }

    filter "system:windows" -- project properties
        systemversion "latest"  -- windows SDK version

        defines
        {
            "GS_PLATFORM_WINDOWS",
            "GS_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        --postbuildcommands   -- DLL file in Engine project moves to Client project
        --{
        --    ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sapphire")
        --}

    filter "configurations:Debug"
        defines "GS_DEBUG"
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
    staticruntime "On"
    language "C++"
    cppdialect "C++17"

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
        "Gemstone/src",
        "Gemstone/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Gemstone"  -- reference to project in the same solution
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "GS_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug"
        defines "GS_DEBUG"
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