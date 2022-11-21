#include "Task.h"
#include <stdlib.h>
#include <iostream>

Task::Task() 
{
	type = (TaskType) (rand()%3); //Randomly select the type of Process
	//Random initialisation of Parameters
	switch (type)
	{
		case simulation:
			executionLength = SIMULATION_EXECUTION_LENGTH_MIN_PARAM + (rand() % SIMULATION_EXECUTION_LENGTH_MAX_PARAM);
			break;
		case IOBound:
			executionLength = IO_EXECUTION_LENGTH_MIN_PARAM + (rand() % IO_EXECUTION_LENGTH_MAX_PARAM);
			break;
		case service:
			executionLength = rand() % SERVICE_EXECUTION_LENGTH_MAX_PARAM;
			break;
	}
	SetState(ready);
};

void Task::Event() //Sleep before resetting state flag to ready
{
	int ms = IO_TIME_EXECUTION_LENGTH_MIN_PARAM + rand() % IO_TIME_EXECUTION_LENGTH_MAX_PARAM;
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	SetState(ready);
}

void Task::Run(int64_t time_quantum) 
{ 
	if (state !=ready)
	{
		std::cout << "Threads should be in a ready state when scheduled!!!\n";
		return;
	}
	SetState(running);
	switch (type)
	{
	case simulation:
		
		std::this_thread::sleep_for(std::chrono::milliseconds(time_quantum));
		executionLength -= time_quantum;
		if (executionLength <= 0)
			SetState(terminated);
		else
			SetState(ready);
		break;
	case IOBound:
	{
		executionLength--;
		if (executionLength <= 0)
		{
			SetState(terminated);
			break;
		}
		if (GetState() == waitingIOCompletion)
			return;
		SetState(waitingIOCompletion);
		std::thread t(&Task::Event, this); //Create a timer thread that will will reset state to ready
		t.detach(); //Detaching the thread to forget about it and automatically release resources
		break;
	}
	case service:
		std::this_thread::sleep_for(std::chrono::milliseconds(rand()% SERVICE_EXECUTION_TIME_PARAM));
		executionLength --;
		if (executionLength <= 0)
			SetState(terminated);
		else
			SetState(ready);
		break;
	}
	if (GetState()==terminated)
		std::cout << "Task " << this->id << " has terminated!\n";
}; //Function will do something

Task::~Task() {};
int Task::GetID() { return id; }
void Task::SetID(int taskId) { id = taskId; }
bool Task::HasTerminated() { return state == terminated; }
bool Task::IsReady() { return state == ready; }
bool Task::IsWaitingForIO() { return state == waitingIOCompletion; }
TaskState Task::GetState() { return state; }
void Task::SetState(TaskState ts) { state = ts; };