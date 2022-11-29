// 2022 Tygo Boons

#include "File.h"
#include "Core/Core.h"

namespace Utils
{
	std::string FileReader::ReadFile(const std::string& filepath)
	{
		// Create filestream and attempt to open file.
		std::fstream myFile;
		myFile.open(filepath, std::ios::in | std::ios::binary);

		ASSERT(myFile, "Could not find file in directory: " + filepath)

		// Create string buffer to read from.
		std::stringstream buffer;
		buffer << myFile.rdbuf();

		// Close the file and free its memory.
		myFile.close();

		// Return a string from the buffer.
		return buffer.str();
	}

	void FileWriter::WriteFile(const std::string& filepath, const std::string& data)
	{
		// Create file and write the data to it.
		std::ofstream myFile(filepath);
		myFile.write(&data[0], data.size());

		LOG("File created in directory: " + filepath)
	}
}