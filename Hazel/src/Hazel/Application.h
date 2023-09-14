#pragma once
#include "Core.h"

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};
	
	// TO BE DEFINED IN CLIENT
	Application* CreateApplication();

}
