#pragma once
#include"../Process/Process.h"
#include"../DS/PriorityQueue.h"
#include"../DS/LinkedList.h"
#include<string>

class Scheduler;
class Processor
{
protected:
	Scheduler* P_Scheduler;// pointer of scheduler class
	Process* RunningProcess;  // pointer to process which is running
	int Total_Busy;//// sum of CT aready run note in ready 
	int Total_TRT; //// sum of TRT
	int PLoad;
	int PUtil;
	int Total_Idle;
	int TimetoFinish; //sum of the CT in ready queue   will also use in calc shotest queue and longest queue 

	int ProcessorNumber;
public:
	Processor();
	Processor(Scheduler* P);

	virtual void AddToReady(Process* P) = 0;
	void AddToRun(Process* P);
	bool ProcessorState()const; // check if the processor is busy or idle when busy return true otherwise return false

	int CalcPLoad();
	int CalcPutil();
	virtual void SchedulerAlgo() = 0;
	int GetTimetoFinish();
	virtual void PrintReady() = 0;
	virtual void PrintRunningProcess()const;
	virtual int CalcTimeToFinish() = 0;
	virtual int NumRDY()const = 0;
};

#include"../Scheduler/Scheduler.h"