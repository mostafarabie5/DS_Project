#include "SJF.h"

SJF::SJF(Scheduler* sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
}

void SJF::SchedulerAlgo()
{
	if (RunningProcess)
	{
		Run();
	}
	else
	{
		if (!ReadyList.isEmpty())
		{
			AddToRun();
		}
	}
}

void SJF::AddToReady(Process* P)
{
	ReadyList.add(P);
	P->SetTransition(P_Scheduler->GetTimeStep());
}

void SJF::PrintReady()
{
	ReadyList.Print();
}

int SJF::NumRDY() const
{
	return ReadyList.getLength();
}

int SJF::CalcTimeToFinish()
{
	return 0;
}

void SJF::AddToRun()
{
	if (!ReadyList.isEmpty())
	{
		Process* ptr;
		ptr = ReadyList.peek();
		if (ptr->getTransition() == P_Scheduler->GetTimeStep())	return;

		ReadyList.remove(1);
		SetRunningProcess(ptr);
	}
}

void SJF::Run()
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
