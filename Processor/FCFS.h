#pragma once
#include "Processor.h"
class FCFS :public Processor
{
	LinkedList<Process*> ReadyList;
	static Queue< Pair*> SIGKILL;   // First is the time ------ Second is the ID
public:
	FCFS(Scheduler * sched_ptr,int num);
	int NumRDY()const; // return number of items in ready list
	void SchedulerAlgo();
	void AddToReady(Process* P);
	void PrintReady();
	int CalcTimeToFinish();
	void AddToRun();
	void Run();
	bool KILLP(int Process_ID);
	static void setSIGKILL(int time,int Id);
};

