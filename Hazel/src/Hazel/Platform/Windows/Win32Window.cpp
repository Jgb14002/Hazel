#include "hzpch.h"

#include "Win32Window.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new Win32Window(properties);
	}

	Win32Window::Win32Window(const WindowProperties& properties)
	{
		Init(properties);
	}

	Win32Window::~Win32Window()
	{
		Shutdown();
	}

	void Win32Window::Init(const WindowProperties& properties)
	{
		m_Data.Title = properties.Title;
		m_Data.Width = properties.Width;
		m_Data.Height = properties.Height;

		HZ_CORE_INFO("Creating window: \"{0}\" ({1}, {2})", properties.Title, properties.Width, properties.Height);
		
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Failed to initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(
			static_cast<int>(properties.Width),
			static_cast<int>(properties.Height),
			m_Data.Title.c_str(),
			nullptr,
			nullptr
		);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSyncEnabled(true);
	}

	void Win32Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Win32Window::SetVSyncEnabled(bool enabled)
	{
		glfwSwapInterval((m_Data.VSyncEnabled = enabled));
	}

	bool Win32Window::IsVSyncEnabled() const
	{
		return false;
	}

	void Win32Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}