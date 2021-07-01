#include "gspch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Gemstone
{
	VertexArray* VertexArray::Create()
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
				return new OpenGLVertexArray();
			}
		}

		GS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void VertexArray::Bind() const
	{	 
	}	 
		 
	void VertexArray::Unbind() const
	{	 
	}	 
		 
	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& VertexBuffer)
	{	 
	}	 
		 
	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer)
	{
	}
}

