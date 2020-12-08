#include "hzpch.h"
#include "Hazel/Platform/Windows/Win32Input.h"
#include "Hazel/Application.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	Input* Input::s_Instance = new Win32Input();

	bool Win32Input::IsKeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Win32Input::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float Win32Input::GetMouseXImpl()
	{
		auto [x, _] = GetMousePositionImpl();
		return x;
	}

	float Win32Input::GetMouseYImpl()
	{
		auto [_, y] = GetMousePositionImpl();
		return y;
	}
	std::pair<float, float> Win32Input::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { static_cast<float>(x), static_cast<float>(y) };
	}
}