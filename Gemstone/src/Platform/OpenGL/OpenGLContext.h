#pragma once

#include "Gemstone/Renderer/GrahpicsContext.h"

struct GLFWwindow;

namespace Gemstone
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}