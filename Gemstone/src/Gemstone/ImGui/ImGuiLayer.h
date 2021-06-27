#pragma once

#include "Gemstone/Core/Layer.h"

#include "Gemstone/Events/KeyEvent.h"
#include "Gemstone/Events/MouseEvent.h"
#include "Gemstone/Events/ApplicationEvent.h"

namespace Gemstone
{
	class GEMSTONE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.f;
	};
}


