#pragma once

#include "Token/TokenUtils.h"

namespace PreProcessor
{
	inline std::vector<size_t> instructionIndices;

	inline void PreProcess(const TokenUtils::TokenList& tokenList)
	{
		for (size_t i = 0; i < tokenList.Size(); i++)
		{
			const Token& token = tokenList[i];
			
			if (token.GetType() != Token::TokenType::INSTRUCTION_STARTER)
				continue;

			instructionIndices.emplace_back(i);
		}
	}

	inline size_t GetTokenIndexFromLine(int line)
	{
		if ((line - 1) >= instructionIndices.size())
		{
			std::cout << "Line [" << line << "] does not exist." << std::endl;
			std::exit(1);
			return 0;
		}

		return instructionIndices[line - 1];
	}
}