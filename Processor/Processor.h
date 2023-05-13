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
	int Total_Busy;//// sum of CT aready run not in ready 
	int Total_TRT; //// sum of TRT
	int PLoad;
	int PUtil;
	int Total_Idle;
	int TimetoFinish; //sum of the CT in ready queue   will also use in calc shotest queue and longest queue  

	int ProcessorNumber;
	bool StopMode;
	int ActiveAtTime;
	
public:
	Processor();
	Processor(Scheduler* P);

	virtual void AddToReady(Process* P) = 0;
	/*virtual void AddToRun() = 0;*/
	bool ProcessorState()const; // check if the processor is busy or idle when busy return true otherwise return false
	void increase_Total_Busy(int x);//will be called in schedalgo before io request or trm 
	void AddTo_Total_TRT(int x);// will be called befor only trm
	int getProcessorNumber(int index);
	float CalcPLoad();
	float CalcPUtil();
	/*int getTotal_Busy();
	int getTotal_TRT();*/
	/*int getPLoad();
	int getPUtil();*/
	virtual void SchedulerAlgo() = 0;
	int GetTimetoFinish();
	virtual void PrintReady() = 0;
	virtual Process* getRunningProcess()const;
	/*virtual int CalcTimeToFinish() = 0;*/
	virtual int NumRDY()const = 0;
	/*virtual void Run() = 0;*/
	void SetRunningProcess(Process* p);
	virtual Process* Delete_FirstProcess() = 0;
	void SetTotal_Idle();
	/**move the process which finished exceution to TRM list
	* @return true when the Running Process finished exceution or false if not*/
	bool MoveToTRM();

	void set_StopMode(bool b);
	bool get_StopMode();
	void set_ActiveAtTime(int n);
	int get_ActiveAtTime();
	virtual bool Ready_isEmpty()=0;

};
#include"../Scheduler/Scheduler.h"