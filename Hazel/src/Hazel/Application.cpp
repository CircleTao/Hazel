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
		// 来创建一个小测试吧
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			HZ_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			HZ_TRACE(e);
		}

		// 在我的VS2022中，在21行处设置断点，一开始并不会掉到这个断点里，而是直接跳过了
		// 并在断点处会显示“无法命中断点，还没有为文档加载任何符号”
		// 重新生成Hazel即可解决这个问题

		while (true);
	}

}