#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <variant>

class Token
{
public:
	enum TokenType
	{
		UNIDENTIFIED,
		STARTER,
		DATA_TYPE,
		IDENTIFIER,
		OPERATOR,
		INT_LITERAL,
		FLOAT_LITERAL,
		BOOL_LITERAL,
		SYSTEM_CALL,
		ENDER
	};

	struct TokenValue
	{
	public:
		TokenValue()
		{

		}

		TokenValue(const std::string& rawValue, TokenType type)
		{

		}

	public:
		template<class T>
		inline T Parsed()
		{
			return std::get<T>(valueVariant);
		}

	private:
		std::variant<int, float, bool, std::string> valueVariant;
	};

public:
	Token()
		: rawValue(""), value(), type(TokenType::UNIDENTIFIED)
	{
	}

	Token(const std::string& rawValue, TokenType type)
		: rawValue(rawValue), value(rawValue, type), type(type)
	{
	}

	Token(const Token& other)
		: rawValue(other.rawValue), value(other.value), type(other.type)
	{
	}

public:
	inline const std::string& GetRawValue() const { return rawValue; }
	inline const TokenValue& GetValue() const { return value; }

private:
	std::string rawValue;
	TokenValue value;
	TokenType type;
};

namespace TokenUtils
{
	typedef std::vector<Token> TokenList;

	inline std::unordered_map<std::string, Token::TokenType> tokenTypeMap
	{
		{"$", Token::TokenType::STARTER},
		{">", Token::TokenType::STARTER},
		{"int", Token::TokenType::DATA_TYPE},
		{"flt", Token::TokenType::DATA_TYPE},
		{"bol", Token::TokenType::DATA_TYPE},
		{"fls", Token::TokenType::BOOL_LITERAL},
		{"tru", Token::TokenType::BOOL_LITERAL},
		{";", Token::TokenType::ENDER},
	};
}