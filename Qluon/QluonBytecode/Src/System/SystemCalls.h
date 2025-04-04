#pragma once

#include "Token/Token.h"
#include "Memory/StackMemory.h"

#include <iostream>
#include <unordered_map>
#include <functional>

namespace SystemCalls
{
	inline std::unordered_map<std::string, std::function<void(const Token&)>> systemCallsMap
	{
		{"cprint", [](const Token& token)
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
						std::cout << StackMemory::Instance().Get<bool>(identifier) << std::endl;
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
					break;
				}
			}
		}
	};
}