#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

namespace Hazel {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// ������һ��С���԰�
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HZ_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HZ_TRACE(e);
		}

		// ���ҵ�VS2022�У���21�д����öϵ㣬һ��ʼ�������������ϵ������ֱ��������
		// ���ڶϵ㴦����ʾ���޷����жϵ㣬��û��Ϊ�ĵ������κη��š�
		// ��������Hazel���ɽ���������

		while (true);
	}

}