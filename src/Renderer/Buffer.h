// 2022 Tygo Boons
// 
// Implemented from other project:
// https://github.com/TygoB-B5/BEngine/tree/Engine/Engine/Src/Renderer

#pragma once

#include <vector>

namespace Renderer
{

	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		// Set vertex data for batch rendering.
		void SetDataDynamic(const std::vector<float>& vertices);

		// Set vertex data for static rendering.
		void SetData(const std::vector<float>& vertices);

		// Bind vertex buffer.
		void Bind();

		// Unbind vertex buffer.
		void UnBind();

	private:
		std::vector<float> m_Vertices;

		uint32_t m_RenderID;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		// Set index data for batch rendering.
		void SetDataDynamic(const std::vector<uint32_t>& indices);

		// Set index data for static rendering.
		void SetData(const std::vector<uint32_t>& indices);

		// Bind index buffer.
		void Bind();

		// Unbind index buffer.
		void UnBind();

		inline uint32_t GetElementCount() const { return static_cast<uint32_t>(m_Indices.size()); }

	private:
		std::vector<uint32_t> m_Indices;

		uint32_t m_RenderID;
	};
}
