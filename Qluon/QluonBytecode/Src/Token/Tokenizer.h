#pragma once

#include "Bytefile/Bytefile.h"
#include "Token.h"

namespace Tokenizer
{
	namespace Utils
	{
		inline bool IsInt(const std::string& s)
		{
			return !s.empty() && std::find_if(s.begin(),
				s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
		}

		inline bool IsFloat(const std::string& s)
		{
			return !s.empty() && std::find_if(s.begin(),
				s.end(), [](unsigned char c) { return !(std::isdigit(c) || c == '.'); }) == s.end();
		}

		inline bool IsSystemCall(const std::string& s)
		{
			return s[0] == '_';
		}

		inline bool IsIdentifier(const std::string& s)
		{
			return s[0] == '!';
		}
	}

	inline TokenUtils::TokenList Tokenize(const Bytefile& byteFile)
	{
		TokenUtils::TokenList tokenList;

		size_t lastIndex = 1;

		for (size_t i = 1; i < byteFile.Length(); i++)
		{
			if (byteFile.GetCharAt(i) == ' ')
			{
				std::string tokenName = byteFile.GetChunk(lastIndex, i);
				Token::TokenType tokenType = Token::TokenType::UNIDENTIFIED;

				if (Utils::IsInt(tokenName))
				{
					tokenType = Token::TokenType::INT_LITERAL;
				}
				else if (Utils::IsFloat(tokenName))
				{
					tokenType = Token::TokenType::FLOAT_LITERAL;
				}
				else if (Utils::IsIdentifier(tokenName))
				{
					tokenType = Token::TokenType::IDENTIFIER;
				}
				else if (Utils::IsSystemCall(tokenName))
				{
					tokenType = Token::TokenType::SYSTEM_CALL;
				}
				else
				{
					tokenType = TokenUtils::tokenTypeMap[tokenName];
				}

				if (tokenType == Token::TokenType::UNIDENTIFIED)
				{
					std::cout << "Illegal token <" << tokenName << "> at [" << i << "]" << std::endl;
					std::exit(1);
				}

				tokenList.emplace_back(tokenName, tokenType);

				lastIndex = i + 1;
			}
		}

		return tokenList;
	}
}