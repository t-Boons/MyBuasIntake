// 2022 Tygo Boons
// 
// Implemented from other project:
// https://github.com/TygoB-B5/BEngine/tree/Engine/Engine/Src/Renderer

#include "mypch.h"
#include "VertexArray.h"
#include "Core/Core.h"

namespace Renderer
{

	uint32_t GlDatatypeSize(uint32_t type)
	{

		// Return size in bytes from Opengl datatype.
		switch (type)
		{
		case GL_FLOAT:        return 4;
		case GL_INT:          return 4;
		case GL_DOUBLE:       return 8;
		case GL_UNSIGNED_INT: return 4;

		default: ASSERT(false, "Datatype not implemented."); return 0;
		}
	}

	VertexArray::VertexArray()
		: m_Stride(0)
	{
		// Generate vertex array object.
		glGenVertexArrays(1, &m_RenderID);
	}

	VertexArray::~VertexArray()
	{
		// Delete vertex array object.
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void VertexArray::SetLayout(const std::vector<VertexDataElement>& vertexElements)
	{
		m_DataElements = vertexElements;

		uint32_t offset = 0;
		m_Stride = 0;

		// Calculate stride based on ever vertex element and amount in vertexElements.
		for (uint32_t i = 0; i < m_DataElements.size(); i++)
		{
			m_Stride += GlDatatypeSize(m_DataElements[i].DataType) * m_DataElements[i].Amount;
		}

		Bind();

		// Set the vertex layout based on the vector of VertexDataElements.
		for (uint32_t i = 0; i < m_DataElements.size(); i++)
		{
			// Enable vertex attribute array of i.
			glEnableVertexAttribArray(i);

			// Set vertex attribute data.
			glVertexAttribPointer(i, m_DataElements[i].Amount, m_DataElements[i].DataType, GL_FALSE, m_Stride, (const void*)offset);

			// Increase offset for next element.
			offset += GlDatatypeSize(m_DataElements[i].DataType) * m_DataElements[i].Amount;
		}
	}

	void VertexArray::Bind()
	{
		// Bind vertex array object.
		glBindVertexArray(m_RenderID);
	}

	void VertexArray::UnBind()
	{
		// Unbind vertex array object.
		glBindVertexArray(0);
	}
}