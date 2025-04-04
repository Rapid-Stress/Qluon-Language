#include "Interpreter.h"
#include "System/SystemCalls.h"

#include <iostream>

Interpreter::Interpreter(const std::string& filePath)
	: byteFile(), filePath(filePath), tokenList()
{
	byteFile = Parser::Parse(filePath);
	tokenList = Tokenizer::Tokenize(byteFile);
}

void Interpreter::Run()
{
	for (size_t tokenIndex = 0; tokenIndex < tokenList.Size(); tokenIndex++)
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
	const Token* dataTypeToken = token.GetNext();
	Token::DataType dataType = dataTypeToken->GetValue().As<Token::DataType>();

	switch (dataType)
	{
	case Token::DataType::INT:
	{
		const Token* identifierToken = dataTypeToken->GetNext();
		const Token* literalToken = identifierToken->GetNext();

		std::string identifier = identifierToken->GetValue().As<std::string>();
		int value = literalToken->GetValue().AsPrimitive<int>();

		StackMemory::Instance().Allocate(identifier, value);
	}
		break;
	case Token::DataType::FLOAT:
	{
		const Token* identifierToken = dataTypeToken->GetNext();
		const Token* literalToken = identifierToken->GetNext();

		std::string identifier = identifierToken->GetValue().As<std::string>();
		float value = literalToken->GetValue().AsPrimitive<float>();

		StackMemory::Instance().Allocate(identifier, value);
	}
		break;
	case Token::DataType::BOOL:
	{
		const Token* identifierToken = dataTypeToken->GetNext();
		const Token* literalToken = identifierToken->GetNext();

		std::string identifier = identifierToken->GetValue().As<std::string>();
		bool value = literalToken->GetValue().AsPrimitive<bool>();

		StackMemory::Instance().Allocate(identifier, value);
	}
		break;
	default:
		break;
	}
}

void Interpreter::HandleSystemCall(const Token& token, size_t& tokenIndex)
{
	const Token* functionLabelToken = token.GetNext();
	std::string functionLabel = functionLabelToken->GetValue().As<std::string>();

	SystemCalls::systemCallsMap[functionLabel](*functionLabelToken);
}
