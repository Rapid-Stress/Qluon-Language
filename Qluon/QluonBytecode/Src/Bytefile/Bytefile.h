#pragma once

#include <string>

class Bytefile
{
public:
	Bytefile()
	{

	}

	Bytefile(const std::string& fileString)
		: fileString(fileString)
	{
	}

public:
	inline const std::string& GetFileString() const { return fileString; }
	inline std::string GetFileStringCopy() const { return std::string(fileString); }
	inline const char* GetFileCString() const { return fileString.c_str(); }
	
	inline size_t Length() const { return fileString.size(); }
	
	inline char GetCharAt(size_t index) const { return fileString[index]; }
	inline std::string GetChunk(size_t start, size_t end) const { return fileString.substr(start, end - start); }

private:
	std::string fileString;
};
