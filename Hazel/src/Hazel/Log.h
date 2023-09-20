#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h" // 加入这个库是为了能够记录自定义类型

namespace Hazel {
	class HAZEL_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_Corelogger; }  // 核心记录器
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_Clientlogger; } //客户端记录器
	private:
		static std::shared_ptr<spdlog::logger> s_Corelogger;
		static std::shared_ptr<spdlog::logger> s_Clientlogger;

		
	};


}

// 核心记录宏
#define HZ_CORE_TRACE(...)    ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZ_CORE_INFO(...)     ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZ_CORE_WARN(...)     ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZ_CORE_ERROR(...)    ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__) 
#define HZ_CORE_FATAL(...)    ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__) 

// 客户端记录宏
#define HZ_TRACE(...)    ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZ_INFO(...)     ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZ_WARN(...)     ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZ_ERROR(...)    ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__) 
#define HZ_FATAL(...)    ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__) 