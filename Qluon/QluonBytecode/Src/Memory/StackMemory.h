#pragma once

#include <iostream>
#include <unordered_map>

const size_t STACK_CAPACITY = 4096;

class StackMemory
{
public:
	enum PrimitiveType
	{
		NOT_PRIMITIVE,
		INT,
		FLOAT,
		BOOL
	};

	struct StackInfo
	{
		StackInfo()
			: location(0), type(PrimitiveType::NOT_PRIMITIVE)
		{
		}

		StackInfo(size_t location, PrimitiveType type)
			: location(location), type(type)
		{
		}

		size_t location;
		PrimitiveType type;
	};

	StackMemory(size_t capacity)
		: stackBuffer(new uint8_t[capacity]), stackPtr(0), capacity(capacity), stackRefs(capacity)
	{
	}

	~StackMemory()
	{
		delete[] stackBuffer;
	}

	StackMemory(const StackMemory&) = delete;
	StackMemory& operator=(const StackMemory&) = delete;

public:
	static StackMemory& Instance()
	{
		static StackMemory instance(STACK_CAPACITY);
		return instance;
	}

public:
	
	template<class T>
	void Allocate(const std::string& identifier, T value)
	{
		AllocateInternal<T>(identifier, value, PrimitiveType::NOT_PRIMITIVE);
	}

	void Allocate(const std::string& identifier, int value)
	{
		AllocateInternal<int>(identifier, value, PrimitiveType::INT);
	}

	void Allocate(const std::string& identifier, float value)
	{
		AllocateInternal<float>(identifier, value, PrimitiveType::FLOAT);
	}

	void Allocate(const std::string& identifier, bool value)
	{
		AllocateInternal<bool>(identifier, value, PrimitiveType::BOOL);
	}

	PrimitiveType GetType(const std::string& identifier)
	{
		auto it = stackRefs.find(identifier);
		if (it == stackRefs.end())
		{
			std::cout << "Variable by identifier: \"" << identifier << "\" does not exist." << std::endl;
			std::exit(1);
		}
		
		return stackRefs[identifier].type;
	}

	template<class T>
	T& Get(const std::string& identifier)
	{
		auto it = stackRefs.find(identifier);
		if (it == stackRefs.end())
		{
			std::cout << "Variable by identifier: \"" << identifier << "\" does not exist." << std::endl;
			std::exit(1);
		}

		T value;
		std::memcpy(&value, stackBuffer + it->second.location, sizeof(T));
		return value;
	}

private:
	template<class T>
	void AllocateInternal(const std::string& identifier, T value, PrimitiveType type)
	{
		if (stackPtr + sizeof(T) > capacity)
		{
			std::cout << "Stack Overflow. Stack size exceeding limit: [" << capacity << "bytes]" << std::endl;
			std::exit(1);
		}

		std::memcpy(stackBuffer + stackPtr, &value, sizeof(T));
		stackRefs[identifier] = StackInfo(stackPtr, type);
		stackPtr += sizeof(T);
	}

private:
	uint8_t* stackBuffer;
	size_t stackPtr;
	size_t capacity;

	std::unordered_map<std::string, StackInfo> stackRefs;
};
