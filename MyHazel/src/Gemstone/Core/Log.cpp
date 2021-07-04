#include "gspch.h"

#include "spdlog/sinks/stdout_color_sinks.h"
//#include "spdlog/sinks/basic_file_sink.h"

namespace Gemstone
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// Set the log message format
		spdlog::set_pattern("%^[%T] %n: %v%$");
		// Create consoles
		// for engine
		s_CoreLogger = spdlog::stdout_color_mt("GEMSTONE");
		s_CoreLogger->set_level(spdlog::level::trace);
		// for client
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}