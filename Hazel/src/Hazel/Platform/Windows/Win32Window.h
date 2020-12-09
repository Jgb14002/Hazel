#pragma once

#include "Hazel/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProperties& properties);
		virtual ~Win32Window();

		virtual void OnUpdate() override;

		virtual inline unsigned int GetWidth() const override { return m_Data.Width; }
		virtual inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline virtual void* GetNativeWindow() const override
		{
			return static_cast<void*>(m_Window);
		}

		virtual inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		virtual void SetVSyncEnabled(bool enabled) override;
		virtual bool IsVSyncEnabled() const override;
	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width;
			unsigned int Height;
			bool VSyncEnabled;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}
