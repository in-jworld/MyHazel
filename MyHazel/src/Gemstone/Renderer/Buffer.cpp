#include "gspch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
//#include "Platform/Direct3D/Direct3DBuffer.h"

namespace Gemstone
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
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
				return new OpenGLVertexBuffer(vertices, size);
			}
		}

		GS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
				return new OpenGLIndexBuffer(indices, count);
			}
		}

		GS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}