// 2022 Tygo Boons

#pragma once

namespace Utils
{

	class FileReader
	{
	public:
		static std::string ReadFile(const std::string& filepath);
	};

	class FileWriter
	{
	public:
		static void WriteFile(const std::string& filepath, const std::string& data);
	};
}