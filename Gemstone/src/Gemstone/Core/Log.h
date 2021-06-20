#pragma once

#include <memory>

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Gemstone
{
	class GEMSTONE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define GS_CORE_TRACE(...)		::Gemstone::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GS_CORE_INFO(...)		::Gemstone::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GS_CORE_WARN(...)		::Gemstone::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GS_CORE_ERROR(...)		::Gemstone::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GS_CORE_CRITICAL(...)	::Gemstone::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GS_TRACE(...)			::Gemstone::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GS_INFO(...)			::Gemstone::Log::GetClientLogger()->info(__VA_ARGS__)
#define GS_WARN(...)			::Gemstone::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GS_ERROR(...)			::Gemstone::Log::GetClientLogger()->error(__VA_ARGS__)
#define GS_CRITICAL(...)		::Gemstone::Log::GetClientLogger()->critical(__VA_ARGS__)

