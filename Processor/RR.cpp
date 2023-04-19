#include "RR.h"

RR::RR(Scheduler*sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
	tt = 0;
}

void RR::SchedulerAlgo()
{
	if (RunningProcess)
	{
		if (RunningProcess->getRemainingTime() == 0)
		{
			P_Scheduler->AddToTRM(RunningProcess);
			if (!ReadyQueue.isEmpty())
			{
				ReadyQueue.dequeue(RunningProcess);
			}
			else
			{
				RunningProcess = nullptr;
			}
			tt = 0;
		}
		else 
		{
			RunningProcess->DecreaseRemainingTime();
			tt++;
			if (tt == P_Scheduler->GetTS())
			{
				ReadyQueue.enqueue(RunningProcess);
				ReadyQueue.dequeue(RunningProcess);
				tt = 0;
				return;
				
			}
			Run();
		}
		
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
	ReadyQueue.enqueue(P);
}

void RR::PrintReady()
{

	std::cout << "Processor " << ProcessorNumber << " [RR  ]: ";
	ReadyQueue.Print(NumRDY(), " RDY: ");

}


int RR::CalcTimeToFinish()
{
	return 0;
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
		ReadyQueue.dequeue(ptr);
		SetRunningProcess(ptr);
	}
}

void RR::Run()
{
	srand(time(0));
	int r = rand() % 100 + 1;
	if (r >= 1 && r <= 15)
	{
		P_Scheduler->AddToBLK(RunningProcess);
		SetRunningProcess(nullptr);

	}

	else if (r >= 20 && r <= 30)
	{
		SetRunningProcess(nullptr);
		AddToReady(RunningProcess);
	}
	else if (r >= 50 && r <= 60)
	{
		P_Scheduler->AddToTRM(RunningProcess);
		SetRunningProcess(nullptr);
	}
}
