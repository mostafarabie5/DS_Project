#pragma once
#include "Processor.h"
class FCFS :public Processor
{
	LinkedList<Process*> ReadyList;
	static Queue< Pair*> SIGKILL;   // First is the time ------ Second is the ID
public:
	FCFS(Scheduler* sched_ptr, int num);
	int NumRDY()const; // return number of items in ready list
	void SchedulerAlgo();
	void AddToReady(Process* P);
	void PrintReady();
	static void setSIGKILL(int time,int Id);
	//Delete the first non forked process from FCFS
	Process* Delete_FirstProcess();
	/*Search for the process which I recieve signal to kill to and move it to TRM Queue
	@return true when the required process is found in that processor or false if not*/
	bool KillProcess();
	/*Search for the index of the child process in the ready list to move it to TRM queue and remove it from the Processor
	@param pointer the child process
	@return true if the child process is found in that Processor or false if not*/
	bool OrphanPosition(Process*& p);
	/*remove the Kill Signal after use it with the process*/
	void popKillSignal();

	bool Ready_isEmpty();

	void AddForkedProcess();
	//Remove first process from the ready list (forked or not) when Overheat Processor
	Process* removeProcess();   
};

