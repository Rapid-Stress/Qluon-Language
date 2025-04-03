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
	for (size_t tokenIndex = 0; tokenIndex < tokenList.size(); tokenIndex++)
	{
		const Token& token = tokenList[tokenIndex];
		ExecuteToken(token, tokenIndex);
	}
}

void Interpreter::ExecuteToken(const Token& token, size_t& tokenIndex)
{
	switch (token.GetType())
	{
	case Token::TokenType::INSTRUCTION_STARTER:
		Token::InstructionType starterType = token.GetValue().As<Token::InstructionType>();

		switch (starterType)
		{
		case Token::InstructionType::VARIABLE_DEFINE:
			HandleVariableDefine(token, tokenIndex);
			break;
		case Token::InstructionType::FUNCTON_INVOKE:
			HandleSystemCall(token, tokenIndex);
			break;
		}
		break;
	}
}

void Interpreter::HandleVariableDefine(const Token& token, size_t& tokenIndex)
{
	std::cout << "Define Variable" << std::endl;
	std::cin.get();
}

void Interpreter::HandleSystemCall(const Token& token, size_t& tokenIndex)
{

}
