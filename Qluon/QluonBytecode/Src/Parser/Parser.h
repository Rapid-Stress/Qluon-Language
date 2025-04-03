#pragma once

#include "Bytefile/Bytefile.h"

#include <sstream>
#include <fstream>

namespace Parser
{
	inline Bytefile Parse(const std::string& path)
	{
		std::ifstream file(path);
		std::stringstream buffer;

		buffer << file.rdbuf();

		std::string fileString = buffer.str();

		while (true)
		{
			size_t newLinePos = fileString.find_first_of("\n\r");
			if (newLinePos == std::string::npos)
				break;

			fileString[newLinePos] = ' ';
		}

		size_t lastSpacePos = fileString.find_first_of(' ');

		while (true)
		{
			size_t spacePos = fileString.find_first_of(' ', lastSpacePos + 1);
			if (spacePos == std::string::npos)
				break;

			if (lastSpacePos == spacePos - 1)
			{
				fileString.erase(spacePos, 1);
				spacePos = lastSpacePos;
			}

			lastSpacePos = spacePos;
		}

		if (fileString[0] != ' ')
			fileString.insert(0, " ");

		Bytefile byteFile(fileString);

		return byteFile;
	}
}