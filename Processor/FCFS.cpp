#include "FCFS.h"
#include <cstdlib>
#include<ctime>
FCFS::FCFS(Scheduler * sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
}


int FCFS::NumRDY()const
{
	return ReadyList.getLength();
}

void FCFS::SchedulerAlgo()
{
	
	if (!RunningProcess)
	{
		if (!ReadyList.isEmpty())
		{
			Process* P;
			P = Delete_FirstProcess();
			RunningProcess = P;
		}
	}
	else
	{
		Total_Busy++;
		RunningProcess->DecreaseRemainingTime();
		if(!MoveToTRM())
			if (RunningProcess->blk_request(RunningProcess->getCT() - RunningProcess->getRemainingTime()))
			{
				P_Scheduler->AddToBLK(RunningProcess);
				RunningProcess = nullptr;
			}
	}
}

void FCFS::AddToReady(Process* P)
{
	ReadyList.InsertEnd(P);
	TimetoFinish += P->getCT();
}

void FCFS::PrintReady()
{
	ReadyList.Print();
}

void FCFS::setSIGKILL(int time, int Id)
{
	Pair* p = new Pair;
	p->First = time;
	p->Second = Id;
	SIGKILL.enqueue(p);
}

Process* FCFS::Delete_FirstProcess()
{
	Process* ptr = ReadyList.getEntry(1);
	ReadyList.remove(1);
	TimetoFinish -= ptr->getCT();
	return ptr;
}

bool FCFS::KillProcess()
{
	Pair* Signal;
	bool found=false;
	Process* p = nullptr;
	int Position_ReadyList;
	if (SIGKILL.peek(Signal))
	{

		if (Signal->First == P_Scheduler->GetTimeStep())
		{
			if (RunningProcess&&(RunningProcess->getPID() == Signal->Second))
			{
				P_Scheduler->AddToTRM(RunningProcess);
				KillOrphan(RunningProcess->GetChild());
				RunningProcess = nullptr;
				found = true;
			}
			else
			{
				for (int i = 1; i <= ReadyList.getLength() && !found; i++)
				{
					p = ReadyList.getEntry(i);
					if (p->getPID() == Signal->Second)
					{
						found = true;
						Position_ReadyList = i;
					}
				}
				if (found)
				{
					P_Scheduler->AddToTRM(p);
					ReadyList.remove(Position_ReadyList);
					KillOrphan(p->GetChild());
				}
			}
			if (found)
			{
				SIGKILL.dequeue(Signal);
				SIGKILL.peek(Signal);
				found = false;
			}
		}
		
	}
	return found;
}

void FCFS::KillOrphan(Process* p)
{
	if (!p)
		return;
	P_Scheduler->SearchOrphan(p);
	KillOrphan(p->GetChild());
}

bool FCFS::OrphanPosition(Process*& p)
{
	bool found = false;
	int position;
	Process* temp;
	if (RunningProcess == p)
	{
		P_Scheduler->AddToTRM(RunningProcess);
		RunningProcess = nullptr;
		return true;
	}
	
	for (int i = 1; i <= ReadyList.getLength() && !found; i++)
	{
		temp = ReadyList.getEntry(i);
		if (p->getPID() == temp->getPID())
		{
			found = true;
			position = i;
		}
	}
	if (found)
	{
		P_Scheduler->AddToTRM(p);
		ReadyList.remove(position);
	}
	
	
	return found;
}

void FCFS::popKillSignal()
{
	Pair* p;
	if (!SIGKILL.isEmpty())
	{
		SIGKILL.dequeue(p);
		delete p;
	}
}


Queue<Pair*> FCFS::SIGKILL;
