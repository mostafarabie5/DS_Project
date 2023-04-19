#pragma once
#include "Processor.h"
class RR :public Processor
{
	Queue<Process*> ReadyQueue;
	int tt;   //time spended in the process   // to count until time slice finish
public:
	RR(Scheduler* sched_ptr,int num);
	void SchedulerAlgo();
	void AddToReady(Process* P);
	void PrintReady();
	int CalcTimeToFinish();
	int NumRDY()const; // return number of items in ready list
	void AddToRun();
	void Run();
};

