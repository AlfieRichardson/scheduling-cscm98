#pragma once
#include "Parameters.h"
#include "Task.h"
#include <list>
#include <thread>
#include <mutex>


class Scheduler;
class Processor
{
private:
	int id;
	std::thread thread;
	volatile bool notEnd = true;
	volatile int64_t quantumTime;
	Task* volatile loadedTask=nullptr;
	Scheduler* parentScheduler;
	std::mutex lock;

public:
	void Running();
public:
	Processor() {  }
	~Processor() {}
	int GetID();
	void SetID(int procId);
	void AttachScheduler(Scheduler* scheduler);
	void StartProcessor();
	void StopProcessor();
	bool LaunchTask(Task& task, int64_t quantum= TIME_QUANTUM_MS);
	bool IsBusy();
};

