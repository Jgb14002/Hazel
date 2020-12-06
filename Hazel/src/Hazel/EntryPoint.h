#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	auto clientApp = Hazel::CreateApplication();
	clientApp->Run();
	delete clientApp;
}

#else
	#error Hazel only supports Windows platform(s)
#endif