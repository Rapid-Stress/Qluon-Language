#pragma once

#include "Bytefile/Bytefile.h"
#include "Token.h"
#include "TokenUtils.h"

const uint32_t TOKEN_BUDGET = 4096;

namespace Tokenizer
{
	inline TokenUtils::TokenList Tokenize(const Bytefile& byteFile)
	{
		TokenUtils::TokenList tokenList(TOKEN_BUDGET);

		size_t lastIndex = 1;

		for (size_t i = 1, tokenIndex = 0; i < byteFile.Length(); i++)
		{
			if (byteFile.GetCharAt(i) == ' ')
			{
				std::string tokenValue = byteFile.GetChunk(lastIndex, i);
				Token::TokenType tokenType = TokenUtils::GetTokenTypeFromValue(tokenValue);

				if (tokenType == Token::TokenType::UNIDENTIFIED)
				{
					std::cout << "Illegal token <" << tokenValue << "> at [" << i << "]." << std::endl;
					std::exit(1);
				}

				tokenList[tokenIndex] = Token(tokenValue, tokenType);
				Token& newToken = tokenList[tokenIndex];
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