#include "gspch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Gemstone
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				GS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
					return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLShader(vertexSrc, fragmentSrc);
			}

			GS_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}

