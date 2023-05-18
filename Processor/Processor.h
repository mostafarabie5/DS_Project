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
	static int Total_TRT; //// sum of TRT
	float PLoad;
	float PUtil;
	int Total_Idle;    //total time which the processor un idel mode
	int TimetoFinish; //sum of the CT in ready queue   will also use in calc shotest queue and longest queue  
	int ProcessorNumber;  //unique number for each processor
	bool StopMode;
	int ActiveAtTime;
	
public:
	/*default constructor*/
	Processor();
	/*parameterized constructor */
	Processor(Scheduler* P);
	/*settre for the process in run mode*/
	void SetRunningProcess(Process* p);
	/*setter for total idel time of that processor */
	void SetTotal_Idle();
	/*setter for stop mode */
	void set_StopMode(bool b);
	/**/
	void set_ActiveAtTime(int n);
	/*return time expected to finish the processes in ready queue*/
	int GetTimetoFinish()const;
	/*return the process that in run mode*/
	virtual Process* getRunningProcess()const;
	/*getter for stop mode*/
	bool get_StopMode()const;
	/**/
	int get_ActiveAtTime()const;
	/*Move process from New Queue to Raedy Queue */
	virtual void AddToReady(Process* P) = 0;
	/**move the process which finished exceution to TRM list
	*@return true when the Running Process finished exceution or false if not*/
	bool MoveToTRM();
	/*check if the processor is busy or idle when busy return true otherwise return false*/
	bool ProcessorState()const;
	/*calculate load persentage */
	float CalcPLoad();
	/*Calculate utility persentage */
	float CalcPUtil();
	/*function that run the process depending on type of the processor*/
	virtual void SchedulerAlgo() = 0;
	/*printing Ready Queue in console*/
	virtual void PrintReady()const = 0;
	/*return number of process exist in ready queue*/
	virtual int NumRDY()const = 0;
	/*delete the first process in ready queue and return it*/
	virtual Process* Delete_FirstProcess() = 0;
	/*Check if ready is empty return true else retrun false */
	virtual bool Ready_isEmpty()const = 0;
	/*Kill all the children of the Parent process which is killed
	@param pointer the child process*/
	void KillOrphan(Process* p);

};

#include"../Scheduler/Scheduler.h"