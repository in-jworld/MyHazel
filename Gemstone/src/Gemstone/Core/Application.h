#pragma once

#include "Core.h"

#include "Window.h"
#include "Gemstone/Events/Event.h"
#include "Gemstone/Events/ApplicationEvent.h"
#include "LayerStack.h"

#include "Gemstone/ImGui/ImGuiLayer.h"

#include "Gemstone/Renderer/Shader.h"
#include "Gemstone/Renderer/Buffer.h"
#include "Gemstone/Renderer/VertexArray.h"

namespace Gemstone
{
	class GEMSTONE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		//unsigned int m_VertexArray;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_Shader2;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};
	
	// To be defined in CLIENT
	Application* CreateApplication();
}