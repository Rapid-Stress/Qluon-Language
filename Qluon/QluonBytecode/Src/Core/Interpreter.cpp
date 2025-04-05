#include "Interpreter.h"
#include "System/SystemCalls.h"
#include "Loader/PreProcessor.h"
#include "Timer/Timer.h"

#include <iostream>

Interpreter::Interpreter(const std::string& filePath)
	: byteFile(), filePath(filePath), tokenList()
{
	byteFile = Parser::Parse(filePath);
	tokenList = Tokenizer::Tokenize(byteFile);
	PreProcessor::PreProcess(tokenList);
}

void Interpreter::Run()
{
	while (Timer::Get().GetProgramCounter() < tokenList.Size())
	{
		const Token& token = tokenList[Timer::Get().GetProgramCounter()];

		ExecuteToken(token);
	}
}

void Interpreter::ExecuteToken(const Token& token)
{
	switch (token.GetType())
	{
	case Token::TokenType::INSTRUCTION_STARTER:
	{
		Token::InstructionType starterType = token.GetValue().As<Token::InstructionType>();

		switch (starterType)
		{
		case Token::InstructionType::VARIABLE_DEFINE:
			HandleVariableDefine(token);
			break;
		case Token::InstructionType::FUNCTON_INVOKE:
			HandleSystemCall(token);
			break;
		}
		break;
	}
	default:
		break;
	}
}

void Interpreter::HandleVariableDefine(const Token& token)
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
	}

	Timer::Get().IncrementProgramCounter(4);
}

void Interpreter::HandleSystemCall(const Token& token)
{
	SystemCalls::Call(token);
}
