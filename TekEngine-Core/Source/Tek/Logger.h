#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace TEK {

	class  Logger
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

#ifdef TEK_DEBUG
#define TEK_CORE_CRITICAL(...) ::TEK::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define TEK_CORE_ERROR(...) ::TEK::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define TEK_CORE_WARN(...) ::TEK::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define TEK_CORE_INFO(...) ::TEK::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define TEK_CORE_TRACE(...) ::TEK::Logger::GetCoreLogger()->trace(__VA_ARGS__)

#define TEK_CRITICAL(...) ::TEK::Logger::GetClientLogger()->critical(__VA_ARGS__)
#define TEK_ERROR(...) ::TEK::Logger::GetClientLogger()->error(__VA_ARGS__)
#define TEK_WARN(...) ::TEK::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define TEK_INFO(...) ::TEK::Logger::GetClientLogger()->info(__VA_ARGS__)
#define TEK_TRACE(...) ::TEK::Logger::GetClientLogger()->trace(__VA_ARGS__)
#else
#define TEK_CORE_CRITICAL(...)
#define TEK_CORE_ERROR(...) 
#define TEK_CORE_WARN(...)
#define TEK_CORE_INFO(...)
#define TEK_CORE_TRACE(...)
#endif

