#pragma once
// Please write all your code in this file. This is an individual coursework, and solutions must not be shared by students.
#include <iostream>
#include "Parameters.h"
#include "Task.h"
#include <list>
#include <thread>
#include "Processor.h"

#include <queue>
#include <mutex>

//The scheduler class should implement scheduling operations required to allow smooth scheduling of all the tasks
class Task;
class Processor;
class Scheduler
{
private:
	Task tasks[NB_TASKS]; //Storing a list of tasks
	Processor processors[NB_PROCESSORS]; //Simulating running processors
private:
	void CreateEnvironment();  //This function should not be modified. Definition is put inside the equivalent cpp file.
public:
	Scheduler(); //This function should not be modified. Definition is put inside the equivalent cpp file.
	~Scheduler();  //This function should not be modified. Definition is put inside the equivalent cpp file.

// own code from here
private:
    std::queue<Task*> taskQ;
    std::mutex lockQ;
    int tasksDone;
public:
	void ScheduleTasksUntilEnd()  //In this function you will have to schedule all the tasks until completion of all of them.
    {
        for (int i = 0; i < NB_TASKS; i++)
        {
            taskQ.push(&tasks[i]);
        }

        tasksDone = 0;

        while (tasksDone < NB_TASKS)
        {
            for (int i = 0; i < NB_PROCESSORS; i++)
            {
                lockQ.lock();
                if (!taskQ.empty() && taskQ.front()->IsReady() && !processors[i].IsBusy())
                {
                    if (processors[i].LaunchTask(*taskQ.front()))
                    {
                        taskQ.pop();
                    }
                }
                lockQ.unlock();
            }
        }
	};


	//The function NotifyEndScheduling is called by the thread representing a processor when done with running a task. This may be of use in some implementations.
	void NotifyEndScheduling(int processor, int taskId, TaskState state)
    {
        lockQ.lock();
        switch (state)
        {
            case TaskState::ready:
                taskQ.push(&tasks[taskId]);
                break;
            case TaskState::waitingIOCompletion:
                taskQ.push(&tasks[taskId]);
                break;
            case TaskState::terminated:
                tasksDone++;
                break;
            case TaskState::done:
                tasksDone++;
                break;
        }
        lockQ.unlock();
	};

	//Complete these two functions. The functions should return your student id and your name.
	int StudentID() { return 851009; }
	std::string StudentName() { return "Alfie Richardson"; }
};


