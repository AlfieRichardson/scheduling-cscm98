// CW Scheduling Processes.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include "Scheduler.h"
#include "Parameters.h"

std::chrono::steady_clock::time_point current_time = std::chrono::steady_clock::now();

void InitClock()
{
	current_time = std::chrono::steady_clock::now();
}

int64_t GetTime()
{
	std::chrono::steady_clock::time_point new_time = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(new_time - current_time).count();
}

int main()
{
	InitClock();
	for (int i = 0; i < NB_SIMULATION_REPEATS; i++)
	{
		Scheduler s;
		s.ScheduleTasksUntilEnd();
#ifdef PRINT_TERMINATION_OUTPUT
		std::cout << "Average Simulation Time (s): " << ((float)GetTime()) / (i+1)/1000. << " s\n";
#endif
	}
	std::cout << "Average Simulation Time (s): " << ((float)GetTime()) / (NB_SIMULATION_REPEATS) / 1000. << " s\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
