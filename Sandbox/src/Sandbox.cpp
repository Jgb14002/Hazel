#include <Hazel.h>

class SandboxLayer : public Hazel::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox Layer") {}

	virtual void OnUpdate() override
	{
		HZ_INFO("SandboxLayer::OnUpdate");
	}

	virtual void OnEvent(Hazel::Event& event) override
	{
		HZ_TRACE("{0}", event);
	}
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}
	~Sandbox() = default;
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}