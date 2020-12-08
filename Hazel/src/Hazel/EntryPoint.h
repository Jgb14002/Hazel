#pragma once

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	auto clientApp = Hazel::CreateApplication();
	clientApp->Run();
	delete clientApp;
}
