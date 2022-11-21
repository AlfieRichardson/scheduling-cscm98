#include "Processor.h"
#include "Scheduler.h"
#include <thread>
#include <chrono>

bool Processor::IsBusy()
{
	bool b=lock.try_lock();
	if (!b)
		return true;
	bool res = loadedTask != nullptr;
	lock.unlock();
	return res;
}
bool Processor::LaunchTask(Task& task, int64_t quantum)  //This function will set/notify a task to carry out by the thread (cf. Running function) representing the processor  
{
	bool b=lock.try_lock();
	if (b)
	{
		if (loadedTask == nullptr)
		{
			loadedTask = &task;      //Setting a task to be run
			quantumTime = quantum;	 //Setting up a time quantum.
		}
		else
		{
			std::cout << "It seems that a task is being loaded while another one is running on the very same processor!\n";
		}
		lock.unlock();
	}
	return b; //returns whether scheduling was sucessful or not. 
}

void Processor::Running() //Entry point of a thread that keeps looping to consume tasks set by the scheduler (cf. Schedule task) 
{
	while (notEnd)
	{
		lock.lock();
		if (loadedTask != nullptr)
		{
			lock.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(CONTEXT_SWITCHING_PENALTY_MS)); //Sleeping the thread to simulate context switching time
			loadedTask->Run(quantumTime);
			Task* task = loadedTask;
			lock.lock();
			loadedTask = nullptr;
			lock.unlock();
			parentScheduler->NotifyEndScheduling(this->id,task->GetID(), task->GetState()); //Calls scheduler to notify end of schduling
		}
		else
			lock.unlock();
	}
}

void Processor::AttachScheduler(Scheduler* scheduler) 
{ 
	parentScheduler = scheduler; 
}

void Processor::StartProcessor() 
{ 
	thread = std::thread(&Processor::Running, this); 
}

void Processor::StopProcessor() 
{ 
	notEnd = false; //Stops the active loop 
	thread.join(); //wait for complete stop of the thread.
}

int Processor::GetID() { return id; }
void Processor::SetID(int procId) { id = procId; }
