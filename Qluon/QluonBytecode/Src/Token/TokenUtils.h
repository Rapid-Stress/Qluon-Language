#pragma once

#include "Token.h"

namespace TokenUtils
{
	class TokenList
	{
	public:
		TokenList()
			: tokenPtr(nullptr), size(0)
		{
		}

		TokenList(size_t size)
			: tokenPtr(new Token[size]), size(size)
		{
		}

		TokenList(const TokenList& other)
			: tokenPtr(new Token[other.size]), size(other.size)
		{
			Token* prev = nullptr;

			for (int i = 0; i < size; i++)
			{
				Token& otherToken = other.tokenPtr[i];
				Token& token = tokenPtr[i];
				token = otherToken;

				if (prev) token.SetPrev(prev);
				if (prev) prev->SetNext(&token);

				prev = &token;
			}
		}

		TokenList(TokenList&& otherTemp) noexcept
			: tokenPtr(otherTemp.tokenPtr), size(otherTemp.size)
		{
			otherTemp.size = 0;
			otherTemp.tokenPtr = nullptr;
		}

		~TokenList()
		{
			delete[] tokenPtr;
		}

	public:
		inline size_t Size() const { return size; }

	public:
		TokenList& operator=(const TokenList& other)
		{
			if (this == &other) return *this;

			delete[] tokenPtr;

			size = other.size;
			tokenPtr = new Token[size];

			Token* prev = nullptr;

			for (int i = 0; i < size; i++)
			{
				Token& otherToken = other.tokenPtr[i];
				Token& token = tokenPtr[i];
				token = otherToken;

				if (prev) token.SetPrev(prev);
				if (prev) prev->SetNext(&token);

				prev = &token;
			}

			return *this;
		}

		TokenList& operator=(TokenList&& otherTemp) noexcept
		{
			size = otherTemp.size;
			tokenPtr = otherTemp.tokenPtr;

			otherTemp.size = 0;
			otherTemp.tokenPtr = nullptr;

			return *this;
		}

		Token& operator[](size_t index)
		{
			if (index < 0 || index >= size)
			{
				std::cout << "Token access out of bounds: [" << index << "] (Token Budget: [" << size << "])" << std::endl;
				std::exit(1);
			}

			return tokenPtr[index];
		}

	private:
		Token* tokenPtr;
		size_t size;
	};

	inline std::unordered_map<std::string, Token::TokenType> tokenTypeMap
	{
		{"$", Token::TokenType::INSTRUCTION_STARTER},
		{">", Token::TokenType::INSTRUCTION_STARTER},
		{"int", Token::TokenType::DATA_TYPE},
		{"flt", Token::TokenType::DATA_TYPE},
		{"bol", Token::TokenType::DATA_TYPE},
		{"fls", Token::TokenType::BOOL_LITERAL},
		{"tru", Token::TokenType::BOOL_LITERAL}
	};

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

	inline Token::TokenType GetTokenTypeFromValue(const std::string& value)
	{
		if (IsInt(value))
			return Token::TokenType::INT_LITERAL;
		else if (IsFloat(value))
			return Token::TokenType::FLOAT_LITERAL;
		else if (IsIdentifier(value))
			return Token::TokenType::IDENTIFIER;
		else if (IsSystemCall(value))
			return Token::TokenType::SYSTEM_CALL;
		else
			return tokenTypeMap[value];
	}

}