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
		SYSTEM_CALL
	};

	enum InstructionType
	{
		VARIABLE_DEFINE,
		FUNCTON_INVOKE,
		LABEL
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
			case TokenType::FLOAT_LITERAL:
				valueVariant = std::stod(rawValue.c_str());
				break;
			case TokenType::BOOL_LITERAL:
				valueVariant = (double)((rawValue == "tru") ? true : false);
				break;
			case TokenType::IDENTIFIER:
			case TokenType::SYSTEM_CALL:
				valueVariant = rawValue.substr(1, rawValue.size() - 1);
				break;
			case TokenType::INSTRUCTION_STARTER:
				switch (rawValue[0])
				{
				case '$':
					valueVariant = InstructionType::VARIABLE_DEFINE;
					break;
				case '>':
					valueVariant = InstructionType::FUNCTON_INVOKE;
					break;
				case '#':
					valueVariant = InstructionType::LABEL;
					break;
				}
				break;
				break;
			case TokenType::DATA_TYPE:
			{
				if (rawValue == "int")
					valueVariant = DataType::INT;
				else if (rawValue == "flt")
					valueVariant = DataType::FLOAT;
				else if (rawValue == "bol")
					valueVariant = DataType::BOOL;
				break;
			}
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

		template<class T>
		inline T AsPrimitive() const
		{
			return (T)std::get<double>(valueVariant);
		}

	private:
		std::variant<double, std::string, InstructionType, DataType> valueVariant;
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