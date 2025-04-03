#pragma once

#include "Parser/Parser.h"
#include "Token/Tokenizer.h"

class Interpreter
{
public:
	Interpreter(const std::string& filePath);

public:
	void Run();

private:
	Bytefile byteFile;
	std::string filePath;
	TokenUtils::TokenList tokenList;
};
