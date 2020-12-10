#pragma once

#include "Hazel/Core.h"

#include <cstdint>

namespace Hazel
{
	enum class ShaderDataType
	{
		None = 0,
		Bool,
		Int, Int2, Int3, Int4,
		Float, Float2, Float3, Float4,
		Mat3, Mat4
	};

	// TODO: Not a fan of these switches - come up with a better solution. 
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:   return 0;
			case ShaderDataType::Bool:   return sizeof(bool);
			case ShaderDataType::Int:    return sizeof(int);
			case ShaderDataType::Int2:   return 2 * sizeof(int);
			case ShaderDataType::Int3:   return 3 * sizeof(int);
			case ShaderDataType::Int4:   return 4 * sizeof(int);
			case ShaderDataType::Float:  return sizeof(float);
			case ShaderDataType::Float2: return 2 * sizeof(float);
			case ShaderDataType::Float3: return 3 * sizeof(float);
			case ShaderDataType::Float4: return 4 * sizeof(float);
			case ShaderDataType::Mat3:   return 3 * 3 * sizeof(float);
			case ShaderDataType::Mat4:   return 4 * 4 * sizeof(float);
		}

		HZ_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}

	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetElementCount()
		{
			switch (Type)
			{
				case ShaderDataType::Bool:
				case ShaderDataType::Int:
				case ShaderDataType::Float:
				{
					return 1;
				}
				case ShaderDataType::Int2:
				case ShaderDataType::Float2:
				{
					return 2;
				}
				case ShaderDataType::Int3:
				case ShaderDataType::Float3:
				{
					return 3;
				}
				case ShaderDataType::Int4:
				case ShaderDataType::Float4:
				{
					return 4;
				}
				case ShaderDataType::None: return 0;
				case ShaderDataType::Mat3: return 9;
				case ShaderDataType::Mat4: return 16;
			}
			HZ_CORE_ASSERT(false, "Unknown shader data type!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements), m_Stride(0)
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.cbegin(); }
		inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.cend(); }
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}