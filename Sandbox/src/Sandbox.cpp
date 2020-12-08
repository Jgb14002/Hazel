#include <Hazel.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>

class SandboxLayer : public Hazel::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox Layer") {}

	virtual void OnUpdate() override
	{
		//HZ_INFO("SandboxLayer::OnUpdate");
	}

	virtual void OnEvent(Hazel::Event& event) override
	{
		HZ_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Sample Text");
		ImGui::End();
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