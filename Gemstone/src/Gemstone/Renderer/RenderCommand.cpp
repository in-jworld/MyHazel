#include "gspch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Gemstone
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}