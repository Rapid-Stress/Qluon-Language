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
		DATA_TYPE,
		IDENTIFIER,
		OPERATOR,
		INT_LITERAL,
		FLOAT_LITERAL,
		BOOL_LITERAL,
		INSTRUCTION_STARTER,
		SYSTEM_CALL,
		INSTRUCTION_ENDER
	};

	enum InstructionType
	{
		VARIABLE_DEFINE,
		FUNCTON_INVOKE,
		LINE_END
	};

	enum DataType
	{
		INT,
		FLOAT,
		BOOL
	};

	struct TokenValue
	{
	public:
		TokenValue()
		{

		}

		TokenValue(const std::string& rawValue, TokenType type)
		{
			switch (type)
			{
			case TokenType::INT_LITERAL:
				valueVariant = std::stoi(rawValue.c_str());
				break;
			case TokenType::FLOAT_LITERAL:
				valueVariant = std::stof(rawValue.c_str());
				break;
			case TokenType::BOOL_LITERAL:
				valueVariant = (rawValue == "tru") ? true : false;
				break;
			case TokenType::IDENTIFIER:
			case TokenType::SYSTEM_CALL:
				valueVariant = rawValue.substr(1, rawValue.size() - 1);
				break;
			case TokenType::INSTRUCTION_ENDER:
			case TokenType::INSTRUCTION_STARTER:
				switch (rawValue[0])
				{
				case '$':
					valueVariant = InstructionType::VARIABLE_DEFINE;
					break;
				case '>':
					valueVariant = InstructionType::FUNCTON_INVOKE;
					break;
				case ';':
					valueVariant = InstructionType::LINE_END;
					break;
				}
				break;
				break;
			case TokenType::DATA_TYPE:
				if (rawValue == "int")
					valueVariant = DataType::INT;
				else if (rawValue == "flt")
					valueVariant = DataType::FLOAT;
				else if (rawValue == "bol")
					valueVariant = DataType::BOOL;
				break;
			case TokenType::OPERATOR:
				valueVariant = rawValue;
				break;
			}
		}

	public:
		template<class T>
		inline T As() const
		{
			return std::get<T>(valueVariant);
		}

	private:
		std::variant<int, float, bool, std::string, InstructionType, DataType> valueVariant;
	};

public:
	Token()
		: rawValue(""), value(), type(TokenType::UNIDENTIFIED), prev(nullptr), next(nullptr)
	{
	}

	Token(const std::string& rawValue, TokenType type)
		: rawValue(rawValue), value(rawValue, type), type(type), prev(nullptr), next(nullptr)
	{
	}

	Token(const Token& other)
		: rawValue(other.rawValue), value(other.value), type(other.type), prev(other.prev), next(other.next)
	{
	}

public:
	inline const std::string& GetRawValue() const { return rawValue; }
	inline const TokenValue& GetValue() const { return value; }

	inline TokenType GetType() const { return type; }

	inline const Token* const GetPrev() const { return prev; }
	inline const Token* const GetNext() const { return next; }

	inline void SetPrev(Token* prev) { this->prev = prev; }
	inline void SetNext(Token* next) { this->next = next; }


private:
	std::string rawValue;
	TokenValue value;
	TokenType type;
	
	Token* prev;
	Token* next;
};

namespace TokenUtils
{
	typedef std::vector<Token> TokenList;

	inline std::unordered_map<std::string, Token::TokenType> tokenTypeMap
	{
		{"$", Token::TokenType::INSTRUCTION_STARTER},
		{">", Token::TokenType::INSTRUCTION_STARTER},
		{"int", Token::TokenType::DATA_TYPE},
		{"flt", Token::TokenType::DATA_TYPE},
		{"bol", Token::TokenType::DATA_TYPE},
		{"fls", Token::TokenType::BOOL_LITERAL},
		{"tru", Token::TokenType::BOOL_LITERAL},
		{";", Token::TokenType::INSTRUCTION_ENDER},
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