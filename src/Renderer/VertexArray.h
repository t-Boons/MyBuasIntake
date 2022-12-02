// 2022 Tygo Boons
// 
// Implemented from other project:
// https://github.com/TygoB-B5/BEngine/tree/Engine/Engine/Src/Renderer

#pragma once

#include "glad/glad.h"

namespace Renderer
{

	struct VertexDataElement
	{
		VertexDataElement(GLuint dataType, GLuint amount)
			: DataType(dataType), Amount(amount)
		{}

		GLuint DataType;
		GLuint Amount;
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		// Set the vertex layout of the vertex array.
		void SetLayout(const std::vector<VertexDataElement>& vertexElements);

		// Bind the vertex array.
		void Bind();

		// Unbind the vertex array.
		void UnBind();

	private:

		std::vector<VertexDataElement> m_DataElements;
		uint32_t m_Stride;

		uint32_t m_RenderID;
	};

}