#pragma once

#include "hzpch.h"

#include "Hazel/Events/Event.h"

namespace Hazel
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(
			const std::string& title = "Application Window",
			unsigned int width = 1280,
			unsigned int height = 720
		) : Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSyncEnabled(bool enabled) = 0;
		virtual bool IsVSyncEnabled() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}