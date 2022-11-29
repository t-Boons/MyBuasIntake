// 2022 Tygo Boons
// 
// Implemented from other project:
// https://github.com/TygoB-B5/BEngine/tree/Engine/Engine/Src/Renderer

#include "Buffer.h"
#include "glad/glad.h"

namespace Renderer
{
	// Vertex buffer.

	VertexBuffer::VertexBuffer()
	{

		// Generate buffer object.
		glGenBuffers(1, &m_RenderID);
	}

	VertexBuffer::~VertexBuffer()
	{
		// Delete vertex buffer object.
		glDeleteBuffers(1, &m_RenderID);
	}

	void VertexBuffer::SetDataDynamic(const std::vector<float>& vertices)
	{
		m_Vertices = vertices;

		Bind();

		// Set buffer data for dynamic vertex buffers.
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
	}

	void VertexBuffer::SetData(const std::vector<float>& vertices)
	{
		m_Vertices = vertices;

		Bind();

		// Set buffer data for static vertex buffers.
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	}

	void VertexBuffer::Bind()
	{
		// Bind current vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
	}

	void VertexBuffer::UnBind()
	{
		// Unbind vertex buffer.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	// Index buffer.


	IndexBuffer::IndexBuffer()
	{
		// Generate buffer object.
		glGenBuffers(1, &m_RenderID);
	}

	IndexBuffer::~IndexBuffer()
	{
		// Delete index buffer object.
		glDeleteBuffers(1, &m_RenderID);
	}

	void IndexBuffer::SetDataDynamic(const std::vector<uint32_t>& indices)
	{
		m_Indices = indices;

		Bind();

		// Set buffer data for dynamic vertex buffers.
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
	}

	void IndexBuffer::SetData(const std::vector<uint32_t>& indices)
	{
		m_Indices = indices;
		
		Bind();

		// Set buffer data for static vertex buffers.
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), &indices[0], GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind()
	{
		// Bind current vertex buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	}

	void IndexBuffer::UnBind()
	{
		// Unbind vertex buffer.
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}