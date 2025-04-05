#pragma once

#include "Loader/Parser.h"
#include "Token/Tokenizer.h"
#include "Token/TokenUtils.h"
#include "Memory/StackMemory.h"

class Interpreter
{
public:
	Interpreter(const std::string& filePath);

public:
	void Run();
	void ExecuteToken(const Token& token);
	
	void HandleVariableDefine(const Token& token);
	void HandleSystemCall(const Token& token);

private:
	Bytefile byteFile;
	std::string filePath;
	TokenUtils::TokenList tokenList;
};
