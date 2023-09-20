#include "hzpch.h"
#include "Log.h"
namespace Hazel {

	std::shared_ptr<spdlog::logger> Log::s_Corelogger;
	std::shared_ptr<spdlog::logger> Log::s_Clientlogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$"); // T-ʱ��� n-��¼������ v-ʵ�ʵ���Ϣ
		s_Corelogger = spdlog::stdout_color_mt("HAZEL"); // ������־
		s_Corelogger->set_level(spdlog::level::trace); //���ô�ӡ����trace-��ӡ��������

		s_Clientlogger = spdlog::stdout_color_mt("APP"); // �ͻ�����־
		s_Clientlogger->set_level(spdlog::level::trace);
	}
 }