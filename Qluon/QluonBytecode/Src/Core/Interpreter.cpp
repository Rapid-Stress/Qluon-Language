#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter(const std::string& filePath)
	: filePath(filePath)
{
	byteFile = Parser::Parse(filePath);
	tokenList = Tokenizer::Tokenize(byteFile);
}

void Interpreter::Run()
{

}