#pragma once

#include "Core.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application() = default;
		virtual ~Application() = default;

		void Run();
	};

	//IMPLEMENTED BY CLIENT APPLICATION
	Application* CreateApplication();
}

