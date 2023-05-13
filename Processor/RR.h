#pragma once
#include "Processor.h"
class RR :public Processor
{
	Queue<Process*> ReadyQueue;
public:
	RR(Scheduler* sched_ptr, int num);
	void SchedulerAlgo();
	void AddToReady(Process* P);
	void PrintReady();
	/*int CalcTimeToFinish();*/
	int NumRDY()const; // return number of items in ready list
	void AddToRun();
	Process* Delete_FirstProcess();
	bool Ready_isEmpty();

};

