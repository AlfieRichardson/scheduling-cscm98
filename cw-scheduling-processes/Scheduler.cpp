#include "Scheduler.h"

Scheduler::Scheduler() //Cosntructor function
{
	CreateEnvironment(); //Destructor function
};
Scheduler::~Scheduler() {
	for (int i = 0; i < NB_PROCESSORS; i++)
		processors[i].StopProcessor();
};

void Scheduler::CreateEnvironment()  //this function should not be modified
{
	//Spining up simulated processors that will be represented by threads
	for (int i = 0; i < NB_PROCESSORS; i++)
	{
		processors[i].SetID(i);
		processors[i].AttachScheduler(this); //Giving access to this scheduler in a Processor object (i.e., for NotifyEndScheduling)
		processors[i].StartProcessor();
	}

	//Initialising tasks
	for (int i = 0; i < NB_TASKS; i++)
		tasks[i].SetID(i);
};