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
		if (event.GetEventType() == Gemstone::EventType::KeyPressed)
		{
			Gemstone::KeyPressedEvent& e = (Gemstone::KeyPressedEvent&)event;
			GS_TRACE("{0}, {1}", event, (char)e.GetKeyCode());
		}
		else
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