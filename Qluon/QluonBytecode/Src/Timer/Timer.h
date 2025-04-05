#pragma once

#include <iostream>
#include <chrono>

class Timer
{
public:
	Timer()
		: programStart(), programCounter()
	{
	}

public:
	static Timer& Get()
	{
		static Timer Instance;
		return Instance;
	}

public:
	inline void RecordStartTime()
	{
		programStart = duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);
	}

	inline void RecordEndTime() const
	{
		std::chrono::milliseconds programEnd = duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);

		std::chrono::milliseconds programDuration = programEnd - programStart;

		std::cout << "Program executed succesfully in: " << programDuration.count() << "ms [" << (float)(programDuration.count() / 1000.0f) << "s]";
	}

	inline size_t GetProgramCounter() const { return programCounter; }
	inline void SetProgramCounter(size_t counter) { programCounter = counter; }
	inline void IncrementProgramCounter(size_t increment) { programCounter += increment; }

private:
	std::chrono::milliseconds programStart;
	size_t programCounter;
};