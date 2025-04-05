#pragma once

#include "Token.h"

namespace TokenUtils
{
	class TokenList
	{
	public:
		TokenList()
			: tokenBuffer(nullptr), size(0)
		{
		}

		TokenList(size_t capacity)
			: tokenBuffer(new Token[capacity]), size(0), capacity(capacity)
		{
		}

		TokenList(const TokenList& other)
			: tokenBuffer(new Token[other.capacity]), size(other.size), capacity(other.capacity)
		{
			Token* prev = nullptr;

			for (int i = 0; i < size; i++)
			{
				Token& otherToken = other.tokenBuffer[i];
				Token& token = tokenBuffer[i];
				token = otherToken;

				if (prev) token.SetPrev(prev);
				if (prev) prev->SetNext(&token);

				prev = &token;
			}
		}

		TokenList(TokenList&& otherTemp) noexcept
			: tokenBuffer(otherTemp.tokenBuffer), size(otherTemp.size), capacity(otherTemp.capacity)
		{
			otherTemp.tokenBuffer = nullptr;
			otherTemp.size = 0;
			otherTemp.capacity = 0;
		}

		~TokenList()
		{
			delete[] tokenBuffer;
		}

	public:
		inline size_t Size() const { return size; }
		inline size_t Capacity() const { return capacity; }

	public:
		TokenList& operator=(const TokenList& other)
		{
			if (this == &other) return *this;

			delete[] tokenBuffer;

			size = other.size;
			capacity = other.capacity;
			tokenBuffer = new Token[capacity];

			Token* prev = nullptr;

			for (int i = 0; i < size; i++)
			{
				Token& otherToken = other.tokenBuffer[i];
				Token& token = tokenBuffer[i];
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
			capacity = otherTemp.capacity;
			tokenBuffer = otherTemp.tokenBuffer;

			otherTemp.size = 0;
			otherTemp.capacity = 0;
			otherTemp.tokenBuffer = nullptr;

			return *this;
		}

		Token& operator[](size_t index) const
		{
			if (index < 0 || index >= capacity)
			{
				std::cout << "Token access out of bounds: [" << index << "] (Token Budget: [" << size << "])." << std::endl;
				std::exit(1);
			}

			size = std::max(size, index);

			return tokenBuffer[index];
		}

	private:
		Token* tokenBuffer;
		mutable size_t size;
		size_t capacity;
	};

	inline std::unordered_map<std::string, Token::TokenType> tokenTypeMap
	{
		{"$", Token::TokenType::INSTRUCTION_STARTER},
		{">", Token::TokenType::INSTRUCTION_STARTER},
		{"#", Token::TokenType::INSTRUCTION_STARTER},
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