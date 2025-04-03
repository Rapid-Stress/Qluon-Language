#pragma once

#include "Bytefile/Bytefile.h"
#include "Token.h"

namespace Tokenizer
{
	inline TokenUtils::TokenList Tokenize(const Bytefile& byteFile)
	{
		TokenUtils::TokenList tokenList;

		size_t lastIndex = 1;

		for (size_t i = 1, tokenIndex = 0; i < byteFile.Length(); i++)
		{
			if (byteFile.GetCharAt(i) == ' ')
			{
				std::string tokenValue = byteFile.GetChunk(lastIndex, i);
				Token::TokenType tokenType = TokenUtils::GetTokenTypeFromValue(tokenValue);

				if (tokenType == Token::TokenType::UNIDENTIFIED)
				{
					std::cout << "Illegal token <" << tokenValue << "> at [" << i << "]" << std::endl;
					std::exit(1);
				}

				Token& newToken = tokenList.emplace_back(tokenValue, tokenType);
				Token* lastToken = (tokenIndex != 0) ? &tokenList[tokenIndex - 1] : nullptr;

				if (lastToken) lastToken->SetNext(&newToken);
				newToken.SetPrev(lastToken);

				lastIndex = i + 1;
				tokenIndex++;
			}
		}

		return tokenList;
	}
}