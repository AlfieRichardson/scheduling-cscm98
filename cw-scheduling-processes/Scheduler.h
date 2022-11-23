#pragma once
// Please write all your code in this file. This is an individual coursework, and solutions must not be shared by students.
#include <iostream>
#include "Parameters.h"
#include "Task.h"
#include <list>
#include <thread>
#include "Processor.h"

#include <queue>

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
    std::queue<Task> taskQ;
public:
	void ScheduleTasksUntilEnd()  //In this function you will have to schedule all the tasks until completion of all of them.
    {
        for (int i = 0; i < NB_TASKS; i++)
        {
            taskQ.push(tasks[i]);
        }

        while (taskQ.empty() == false)
        {
            for (int i = 0; i < NB_PROCESSORS; i++)
            {
                if (taskQ.front().IsReady() && !processors[i].IsBusy()) {
                    if (processors[i].LaunchTask(taskQ.front(), 1000))
                    {
                        taskQ.pop();
                    }
                } else if (taskQ.front().IsWaitingForIO()) {
                    int ioTask = taskQ.front().GetID();
                    taskQ.pop();
                    taskQ.push(tasks[ioTask]);
                }
            }
        }

//        while (true)
//        {
//            for (int i = 0; i < NB_TASKS; i++)
//            {
//                if (tasks[i].HasTerminated() == false)
//                {
//                    break;
//                }
//
//            }
//            break;
//        }

//        while (taskQ.empty() == false)
//        {
//            for (int i = 0; i < NB_PROCESSORS; i++)
//            {
//                if (processors[i].IsBusy() == false)
//                {
//                    do {
//                        if (taskQ.front().IsReady() == true)
//                        {
//                            processors[i].LaunchTask(taskQ.front(), 100);
//                            taskQ.pop();
//                        } else {
//                            int frontID = taskQ.front().GetID();
//                            taskQ.pop();
//                            taskQ.push(tasks[frontID]);
//                        }
//                    } while (processors[i].IsBusy() == false);
//                }
//            }
//        }
	};


	//The function NotifyEndScheduling is called by the thread representing a processor when done with running a task. This may be of use in some implementations.
	void NotifyEndScheduling(int processor, int taskId, TaskState state)
    {
        switch (state)
        {
            case TaskState::ready:
                taskQ.push(tasks[taskId]);
                break;
            case TaskState::waitingIOCompletion:
                taskQ.push(tasks[taskId]);
                break;
            case TaskState::terminated:
                break;
        }
	};

	//Complete these two functions. The functions should return your student id and your name.
	int StudentID() { return 0; }
	std::string StudentName() { return ""; }
};


