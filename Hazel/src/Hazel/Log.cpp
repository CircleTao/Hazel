#include "hzpch.h"
#include "Log.h"
namespace Hazel {

	std::shared_ptr<spdlog::logger> Log::s_Corelogger;
	std::shared_ptr<spdlog::logger> Log::s_Clientlogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // T-时间戳 n-记录器名称 v-实际的消息
		s_Corelogger = spdlog::stdout_color_mt("HAZEL"); // 核心日志
		s_Corelogger->set_level(spdlog::level::trace); //设置打印级别，trace-打印所有内容

		s_Clientlogger = spdlog::stdout_color_mt("APP"); // 客户端日志
		s_Clientlogger->set_level(spdlog::level::trace);
	}
 }