#pragma once

#include "Parser/Parser.h"
#include "Token/Tokenizer.h"
#include "Token/TokenUtils.h"
#include "Memory/StackMemory.h"

class Interpreter
{
public:
	Interpreter(const std::string& filePath);

public:
	void Run();
	void ExecuteToken(const Token& token, size_t& tokenIndex);
	
	void HandleVariableDefine(const Token& token, size_t& tokenIndex);
	void HandleSystemCall(const Token& token, size_t& tokenIndex);

private:
	Bytefile byteFile;
	std::string filePath;
	TokenUtils::TokenList tokenList;
};
