#pragma once
#include <chrono>


class Timer
{
public:

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	auto TimeOfWork() {

		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = end - start;

		return duration.count();
	}


private:

	std::chrono::time_point<std::chrono::steady_clock>  start, end;

};

