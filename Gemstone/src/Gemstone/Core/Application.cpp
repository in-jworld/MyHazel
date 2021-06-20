#include "Application.h"

#include "Gemstone/Events/ApplicationEvent.h"
#include "Gemstone/Core/Log.h"

namespace Gemstone
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			GS_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			GS_TRACE(e);
		}

		while (true);
	}
}





