#pragma once

#ifdef GS_PLATFORM_WINDOWS
	#if GS_DYNAMIC_LINK
		#ifdef GS_BUILD_DLL
			#define GEMSTONE_API __declspec(dllexport)
		#else
			#define GEMSTONE_API __declspec(dllimport)
		#endif
	#else
		#define GEMSTONE_API
	#endif
#else
	#error Gemstone only supports WIndows!
#endif

#ifdef GS_DEBUG
	#define GS_ENABLE_ASSERTS
#endif

#ifdef GS_ENABLE_ASSERTS
	#define GS_ASSERT(x, ...) { if(!(x)) { GS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define GS_CORE_ASSERT(x, ...) { if(!(x)) { GS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define GS_ASSERT(x, ...)
	#define GS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define GS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)