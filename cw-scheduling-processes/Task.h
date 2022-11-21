#pragma once
#include <stdint.h>
#include "Parameters.h"
#include <future> 

//This is a basic definition for the task class. This file should not be modified.

enum TaskType { simulation = 0, IOBound = 1, service = 2 };
enum TaskState { notStarted = 0, ready = 1, terminated=2,running = 3, waitingIOCompletion = 4, done = 5 };

class Processor;
class Task
{
	friend class Processor;
private:
	int64_t sumExecution=0;
	int64_t executionLength; //A parameter that will define the behaviour of the task 
	int id;
	TaskType type;
	volatile TaskState state = notStarted;
private:
	TaskState GetState();
	void SetState(TaskState ts);
public:
	Task() ;
	~Task();
	int GetID();
	void SetID(int taskId);
	void Run(int64_t time_quantum = TIME_QUANTUM_MS);
	bool HasTerminated();
	bool IsReady();
	bool IsWaitingForIO();
	void Event();
};

