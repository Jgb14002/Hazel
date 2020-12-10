#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle) 
	{
		HZ_CORE_ASSERT(windowHandle, "Invalid window handle!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!")

		HZ_CORE_INFO("OpenGL Info: {0} ({1})", glGetString(GL_VERSION), glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}