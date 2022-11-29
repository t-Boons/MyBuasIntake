// 2022 Tygo Boons
// Mesh loading part copied from other project by me.
// https://github.com/TygoB-B5/AlphaEngine/blob/Alpha3D/Alpha/src/Alpha/Objects/MeshRenderer.cpp
// 
// Heavily inspired from.
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#include "Mesh.h"
#include "Core/Core.h"
#include "glm/glm.hpp"

namespace Renderer
{
	Mesh::Mesh()
	{
	}

	bool Renderer::Mesh::LoadMesh(const std::string& filePath)
	{
		// Open file with filepath.
		FILE* file = fopen(filePath.c_str(), "r");

		if (file == NULL)
		{
			LOG_ERROR("Could not open file!")
			return false;
		}


		// Check if filetype is correct.
		const size_t found = filePath.find_last_of(".");
		const std::string fileType = filePath.substr(found + 1);

		if (fileType != "obj")
		{
			LOG_ERROR("No filetype other than .obj supported for now")
			return false;
		}

		std::vector<uint32_t> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> tempVertices;
		std::vector<glm::vec2> tempTexcoords;
		std::vector<glm::vec3> tempNormals;

		// Read file
		while (true)
		{
			char lineData[128] = { 0 };

			int res = fscanf(file, "%s", lineData);

			if (res == EOF)
				break;

			// Vertex
			if (strcmp(lineData, "v") == NULL)
			{
				glm::vec3 vertex = glm::vec3(0);
				auto a = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				tempVertices.push_back(vertex);
			}
			// Vertex Texture Coordinate
			else if (strcmp(lineData, "vt") == NULL)
			{
				glm::vec2 uv = glm::vec3(0);
				auto a = fscanf(file, "%f %f\n", &uv.x, &uv.y);
				tempTexcoords.push_back(uv);
			}
			// Vertex normal
			else if (strcmp(lineData, "vn") == NULL)
			{
				glm::vec3 normal = glm::vec3(0);
				auto a = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				tempNormals.push_back(normal);
			}
			// Indices
			else if (strcmp(lineData, "f") == NULL)
			{
				unsigned int vertexIndex[3] = {}, uvIndex[3] = {}, normalIndex[3] = {};
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				if (matches != 9)
				{
					LOG_ERROR("Indices could not be read! Model probably not triangulated")
					return false;
				}

				// Push back indices in right order
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		// Close the file.
		fclose(file);

		if (vertexIndices.empty())
		{
			LOG_ERROR("File does not contain correct data!")
			return false;
		}

		// Clear any old data that was in the mesh.
		Indices.clear();
		Position.clear();
		Normal.clear();
		TexCoordinate.clear();

		// Fill vertices & indices with correct data
		for (uint32_t i = 0; i < vertexIndices.size(); i++)
		{
			Indices.push_back(i);

			Position.push_back(tempVertices[vertexIndices[i] - 1]);
			TexCoordinate.push_back(tempTexcoords[uvIndices[i] - 1]);
			Normal.push_back(tempNormals[normalIndices[i] - 1]);
		}

		return true;
	}

	bool Mesh::LoadMesh(const float* vertices, uint32_t size)
	{
		uint32_t elementCount = size / VERTEX_SIZE;

		if (size % 8 != 0 || size < 8)
		{
			LOG_ERROR("Incomplete vertex data")
			return false;
		}

		// Fill mesh data.
		for (size_t i = 0; i < elementCount; i++)
		{
			Indices.push_back(i);

			uint32_t index = i * VERTEX_SIZE;

			Position.push_back(glm::vec3(vertices[index]));
			TexCoordinate.push_back(glm::vec2(vertices[index + 3]));
			Normal.push_back(glm::vec3(vertices[index + 5]));
		}

		return true;
	}
}