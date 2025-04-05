#pragma once

#include "Token/Token.h"
#include "Memory/StackMemory.h"
#include "Loader/PreProcessor.h"
#include "Timer/Timer.h"

#include <iostream>
#include <unordered_map>
#include <functional>

namespace SystemCalls
{
	inline std::unordered_map<std::string, std::function<void(const std::string&, const Token&)>> systemCallsMap
	{
		{"jump", [](const std::string& label, const Token& token)
			{
				const Token* jumpIndexToken = token.GetNext();

				switch (jumpIndexToken->GetType())
				{
				case Token::TokenType::INT_LITERAL:
				{
					int jumpIndex = jumpIndexToken->GetValue().AsPrimitive<int>();
					size_t tokenIndexToJump = PreProcessor::GetTokenIndexFromLine(jumpIndex);
					Timer::Get().SetProgramCounter(tokenIndexToJump);
				}
					break;
				default:
					std::cout << "Invalid argument token <" << jumpIndexToken->GetRawValue() << "> passed into system function \""
						<< label << "\"." << std::endl;
					std::exit(1);
					break;
				}
			}
		},
		{"cprint", [](const std::string& label, const Token& token)
			{
				const Token* tokenToPrint = token.GetNext();

				switch (tokenToPrint->GetType())
				{
				case Token::TokenType::IDENTIFIER:
				{
					const std::string& identifier = tokenToPrint->GetValue().As<std::string>();
					StackMemory::PrimitiveType type = StackMemory::Instance().GetType(identifier);

					switch (type)
					{
					case StackMemory::PrimitiveType::INT:
						std::cout << StackMemory::Instance().Get<int>(identifier) << std::endl;
						break;
					case StackMemory::PrimitiveType::FLOAT:
						std::cout << StackMemory::Instance().Get<float>(identifier) << std::endl;
						break;
					case StackMemory::PrimitiveType::BOOL:
						std::cout << (StackMemory::Instance().Get<bool>(identifier) ? "true" : "false") << std::endl;
						break;
					case StackMemory::PrimitiveType::NOT_PRIMITIVE:
						break;
					}
				}
					break;
				case Token::TokenType::INT_LITERAL:
					std::cout << tokenToPrint->GetValue().AsPrimitive<int>() << std::endl;
					break;
				case Token::TokenType::FLOAT_LITERAL:
					std::cout << tokenToPrint->GetValue().AsPrimitive<float>() << std::endl;
					break;
				case Token::TokenType::BOOL_LITERAL:
					std::cout << tokenToPrint->GetValue().AsPrimitive<bool>() << std::endl;
					break;
				default:
					std::cout << "Invalid argument token <" << tokenToPrint->GetRawValue() << "> passed into system function \"" 
						<< label << "\"." << std::endl;
					std::exit(1);
					break;
				}

				Timer::Get().IncrementProgramCounter(3);
			}
		}
	};

	inline void Call(const Token& token)
	{
		const Token* functionLabelToken = token.GetNext();
		std::string functionLabel = functionLabelToken->GetValue().As<std::string>();

		auto it = systemCallsMap.find(functionLabel);
		if (it == systemCallsMap.end())
		{
			std::cout << "Call to system function \"" << functionLabel << "\" does not exists or is invalid.";
			std::exit(1);
		}

		SystemCalls::systemCallsMap[functionLabel](functionLabel, *functionLabelToken);
	}
}