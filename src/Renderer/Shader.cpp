// 2022 Tygo Boons
//
// Implementation from other project by me:
// https://github.com/TygoB-B5/BEngine/blob/Engine/Engine/Src/Renderer/Shader.cpp
// Inspiration:
// https://www.khronos.org/opengl/wiki/Shader_Compilation

#include "mypch.h"
#include "Shader.h"
#include "Core/Core.h"
#include "Utils/File.h"
#include "glad/glad.h"

namespace Renderer
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		return 0;
	}

	Shader::Shader(const std::string& filepath)
	{
		std::string src = Utils::FileReader::ReadFile(filepath);

		m_Sources = PreProcess(src);
		Compile(m_Sources);
	}

	Shader::~Shader()
	{
		UnBind();
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind()
	{
		ASSERT(m_RendererID, "Shader has not been compiled.")
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& uniformName, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glProgramUniformMatrix4fv(m_RendererID, location, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::UploadUniformMat3(const std::string& uniformName, const glm::mat3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glProgramUniformMatrix3fv(m_RendererID, location, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::UploadUniformMat2(const std::string& uniformName, const glm::mat2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glProgramUniformMatrix2fv(m_RendererID, location, 1, GL_FALSE, &value[0][0]);
	}

	void Shader::UploadUniformFloat(const std::string& uniformName, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glProgramUniform1f(m_RendererID, location, value);
	}

	void Shader::UploadUniformInt(const std::string& uniformName, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glProgramUniform1i(m_RendererID, location, value);
	}

	void Shader::UploadUniformVec3(const std::string& uniformName, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glProgramUniform3f(m_RendererID, location, value.x, value.y, value.z);
	}

	void Shader::UploadUniformVec4(const std::string& uniformName, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glProgramUniform4f(m_RendererID, location, value.x, value.y, value.z, value.w);
	}

	void Shader::UploadUniformTextureSlot(const std::string& uniformName, int value)
	{
		UploadUniformInt(uniformName, value);
	}

	std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> sources;

		// Set shader type prefix and get the length in elements.
		const char* shaderTypePrefix = "#type";
		uint32_t shaderTypeLength = strlen(shaderTypePrefix);

		// Find begin position of source files.
		uint32_t pos = source.find(shaderTypePrefix, 0);

		// NOTE: pos < INT_MAX used for 64bit applications
		while (pos != std::string::npos && pos < INT_MAX)
		{
			// Find source begin
			uint32_t begin = pos + shaderTypeLength + 1;

			// find first newline starting search from pos.
			uint32_t endOfLine = source.find_first_of("\r\n", pos);

			// Get the opengl enum shader type as a string.
			std::string type = source.substr(begin, endOfLine - begin);

			ASSERT(ShaderTypeFromString(type), "#type (shaderType) Syntax error.")

			// Get position of the next newline.
			uint32_t nextLinePos = source.find_first_of("\r\n", endOfLine);

			// Set pos to the next shaderTypePrefix.
			pos = source.find(shaderTypePrefix, nextLinePos);

			// Add shader type and source code to map.
			sources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return sources;
	}

	void Shader::Compile(const std::unordered_map<GLenum, std::string>& sources)
	{
		// Create shader program.
		GLuint program = glCreateProgram();

		std::vector<GLenum> shaderIds;

		for(std::pair<GLenum, std::string> source : sources)
		{
			// Create a gl shader object.
			GLuint shader;
			shader = glCreateShader(source.first);

			// Attach the shader source code to the shader object.
			const char* src = source.second.c_str();
			glShaderSource(shader, 1, &src, NULL);

			// Compile the shader.
			glCompileShader(shader);

			// Check if compilation was successful. if not assert and give the error.
			GLint success;
			char infoLog[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				std::string shaderType = "Fragment Shader";

				if (source.first == GL_VERTEX_SHADER)
				{
					shaderType = "Vertex Shader\n";
				}
				glGetShaderInfoLog(shader, 512, NULL, infoLog);
				ASSERT(false, shaderType + std::string(infoLog))
				glDeleteShader(shader);
			}

			// Attach shader to program.
			glAttachShader(program, shader);

			// Add compiled shader to temporary shader id collection.
			shaderIds.push_back(shader);
		}

		// Link all the compiled shader programs.
		glLinkProgram(program);


		GLint success;
		char infoLog[512];

		// Check if linking was successful.
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			ASSERT(false, std::string(infoLog))
			glDeleteProgram(program);
		}

		// Delete shaders.
		for (GLuint shaderId : shaderIds)
		{
			glDeleteShader(shaderId);
		}

		// Set program to render ID.
		m_RendererID = program;
	}

}