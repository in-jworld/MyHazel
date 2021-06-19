#pragma once

#ifdef GS_PLATFORM_WINDOWS
	#ifdef GS_BUILD_DLL
		#define GEMSTONE_API __declspec(dllexport)
	#else
		#define GEMSTONE_API __declspec(dllimport)
	#endif
#else
	#error Gemstone only supports WIndows!
#endif