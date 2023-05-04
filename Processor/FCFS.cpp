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
	if (!ReadyList.isEmpty())
	{
		if (!RunningProcess)
		{
			Process* P;
			P = ReadyList.getEntry(1);
			RunningProcess = P;
			ReadyList.remove(1);
			Total_Busy -= RunningProcess->getCT();
		}
		else
		{
			RunningProcess->DecreaseRemainingTime();
			if (RunningProcess->getRemainingTime() == 0)
			{
				P_Scheduler->AddToTRM(RunningProcess);
				RunningProcess = nullptr;
				SchedulerAlgo();
			}
		}
	}
}

void FCFS::AddToReady(Process* P)
{
	ReadyList.InsertEnd(P);
	Total_Busy += P->getCT();
	P->SetTransition(P_Scheduler->GetTimeStep());
}

void FCFS::PrintReady()
{
	ReadyList.Print();
}

int FCFS::CalcTimeToFinish()
{
	return 0;
}

void FCFS::AddToRun()
{
	if (!ReadyList.isEmpty())
	{
		Process* ptr;
		ptr = ReadyList.getEntry(1);
		if (ptr->getTransition() == P_Scheduler->GetTimeStep())	return;

		ReadyList.remove(1);
		SetRunningProcess(ptr);
	}
}

void FCFS::Run()
{
	int r = rand() % 100 + 1;
	if (RunningProcess->getTransition() == P_Scheduler->GetTimeStep())
		return;
	if (r >= 1 && r <= 15)
	{
		P_Scheduler->AddToBLK(RunningProcess);
		SetRunningProcess(nullptr);

	}
	else if (r >= 20 && r <= 30)
	{
		AddToReady(RunningProcess);
		SetRunningProcess(nullptr);

	}
	else if (r >= 50 && r <= 60)
	{
		P_Scheduler->AddToTRM(RunningProcess);
		SetRunningProcess(nullptr);
	}
}

bool FCFS::KILLP(int Process_ID)
{
	return true;
}

void FCFS::setSIGKILL(int time, int Id)
{
	Pair* p = new Pair;
	p->First = time;
	p->Second = Id;
	SIGKILL.enqueue(p);
}

Queue<Pair*> FCFS::SIGKILL;
