#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:   HZ_CORE_ASSERT(false, "Headless mode is not currently supported."); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		HZ_CORE_ASSERT(false, "Unknkown renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:   HZ_CORE_ASSERT(false, "Headless mode is not currently supported."); return nullptr;
			case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		HZ_CORE_ASSERT(false, "Unknkown renderer API!");
		return nullptr;
	}
}