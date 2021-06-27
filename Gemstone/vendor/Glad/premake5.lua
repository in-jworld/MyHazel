project "Glad"
	kind "StaticLib"
	staticruntime "On"
	language "C"

	targetdir ("bin/" .. outputdir .. "%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "%{prj.name}")

	files
	{
		"include/Glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"