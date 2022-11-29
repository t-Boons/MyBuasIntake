// 2022 Tygo Boons
// 
// Implemented from other project:
// https://github.com/TygoB-B5/BEngine/tree/Engine/Engine/Src/Renderer

#pragma once

#include "Core/Core.h"
#include "VertexArray.h"
#include "Buffer.h"

namespace Renderer
{

	// This class will be a container for renderable data.

	class VertexData
	{
	public:
		VertexData();
		VertexData(const std::vector<VertexDataElement>& layout, const std::vector<float>& vertices, const std::vector<uint32_t>& indices);

		// Set various types of data.

		void SetVertexLayout(const std::vector<VertexDataElement>& layout);
		void SetVertexData(const std::vector<float>& vertices);
		void SetIndexData(const std::vector<uint32_t>& indices);

		void SetVertexDataDynamic(const std::vector<float>& vertices);
		void SetIndexDataDynamic(const std::vector<uint32_t>& indices);


		// Getters
		const RefPtr<VertexArray> GetVertexArray() const { return m_VertexArray; }
		const RefPtr<VertexBuffer> GetVertexBuffer() const { return m_VertexBuffer; }
		const RefPtr<IndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		void Init();

	private:
		RefPtr<VertexArray> m_VertexArray;
		RefPtr<VertexBuffer> m_VertexBuffer;
		RefPtr<IndexBuffer> m_IndexBuffer;
	};
}