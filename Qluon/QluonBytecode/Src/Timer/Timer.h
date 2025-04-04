#pragma once

#include <iostream>
#include <chrono>

namespace Timer
{
	inline std::chrono::milliseconds programStart;

	inline void RecordStartTime()
	{
		programStart = duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);
	}

	inline void RecordEndTime()
	{
		std::chrono::milliseconds programEnd = duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);

		std::chrono::milliseconds programDuration = programEnd - programStart;

		std::cout << "Program executed succesfully in: " << programDuration.count() << "ms [" << (float)(programDuration.count() / 1000.0f) << "s]";
	}
}