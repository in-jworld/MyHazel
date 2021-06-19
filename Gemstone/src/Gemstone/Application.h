#pragma once

#include "Core.h"

namespace Gemstone
{
	class GEMSTONE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


