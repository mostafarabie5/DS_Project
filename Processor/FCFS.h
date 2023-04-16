#pragma once
#include "Processor.h"
class FCFS :public Processor
{
	LinkedList<Process*> ReadyList;
public:
	FCFS(int num);
	int NumRDY()const; // return number of items in ready list
	void SchedulerAlgo();
	void AddToReady(Process* P);
	void PrintReady();
	int CalcTimeToFinish();
	void AddToRun();
	void Run();
};

