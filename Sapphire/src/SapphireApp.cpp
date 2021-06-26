#include <Gemstone.h>

class ExampleLayer : public Gemstone::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		GS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Gemstone::Event& event) override
	{
		GS_TRACE("{0}", event);
	}
};

class Sapphire : public Gemstone::Application
{
public:
	Sapphire()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Gemstone::ImGuiLayer());
	}

	~Sapphire()
	{

	}
};

Gemstone::Application* Gemstone::CreateApplication()
{
	return new Sapphire();
}