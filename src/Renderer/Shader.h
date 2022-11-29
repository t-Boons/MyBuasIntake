// 2022 Tygo Boons
//
// Implementation from other project by me:
// https://github.com/TygoB-B5/BEngine/blob/Engine/Engine/Src/Renderer/Shader.h
//

#pragma once

#include <string>
#include <unordered_map>
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace Renderer
{

	class Shader
	{
	public:
		// Create a shader instance with filepath to shader.
		Shader(const std::string& filepath);

		~Shader();

		// Bind this shader.
		void Bind();

		// Unbind this shader.
		void UnBind();

		// Upload different variable types to shader.
		void UploadUniformMat4(const std::string& uniformName, const glm::mat4& value);
		void UploadUniformMat3(const std::string& uniformName, const glm::mat3& value);
		void UploadUniformMat2(const std::string& uniformName, const glm::mat2& value);
		void UploadUniformFloat(const std::string& uniformName, float value);
		void UploadUniformInt(const std::string& uniformName, int value);
		void UploadUniformVec3(const std::string& uniformName, const glm::vec3& value);
		void UploadUniformVec4(const std::string& uniformName, const glm::vec4& value);
		void UploadUniformTextureSlot(const std::string& uniformName, int value);

	private:
		// Split ever shader type to type and source.
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		// Compile every shader in the map by type and source.
		void Compile(const std::unordered_map<GLenum, std::string>& sources);

	private:
		std::unordered_map<GLenum, std::string> m_Sources;
		GLuint m_RendererID;
	};


}