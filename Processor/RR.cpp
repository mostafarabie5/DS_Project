#include "RR.h"

RR::RR(Scheduler*sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
}

void RR::SchedulerAlgo()
{
	if (RunningProcess)
	{
		Run();
	}
	else
	{
		if (!ReadyQueue.isEmpty())
		{
			AddToRun();
		}
	}

}

void RR::AddToReady(Process* P)
{
	TimetoFinish += P->getCT();
	ReadyQueue.enqueue(P);
	P->SetTransition(P_Scheduler->GetTimeStep());
}

void RR::PrintReady()
{
	ReadyQueue.Print(NumRDY(), " RDY: ");
}


int RR::NumRDY() const
{
	return ReadyQueue.Getcount();
}

void RR::AddToRun()
{
	if (!ReadyQueue.isEmpty())
	{
		Process* ptr=nullptr;
		ReadyQueue.peek(ptr);
		if (ptr->getTransition() == P_Scheduler->GetTimeStep())	return;

		ReadyQueue.dequeue(ptr);
		SetRunningProcess(ptr);
		TimetoFinish -= ptr->getCT();
	}
}

void RR::Run()
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

Process* RR::Delete_FirstProcess()
{
	Process* ptr = nullptr;
	ReadyQueue.dequeue(ptr);
	return ptr;
}

