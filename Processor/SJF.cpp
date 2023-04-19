#include "SJF.h"

SJF::SJF(Scheduler* sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
}

void SJF::SchedulerAlgo()
{
	if (RunningProcess)
	{
		if (RunningProcess->getRemainingTime() == 0)
		{
			P_Scheduler->AddToTRM(RunningProcess);
			if (!ReadyList.isEmpty())
			{
				AddToRun();
			}
			else
			{
				RunningProcess = nullptr;
			}
		}
		else
		{
			RunningProcess->DecreaseRemainingTime();
			Run();
		}
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
}

void SJF::PrintReady()

{

	std::cout << "Processor " << ProcessorNumber << " [SJF ]: ";
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
		ReadyList.remove(1);
		SetRunningProcess(ptr);
	}
}

void SJF::Run()
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
		AddToReady(RunningProcess);
		SetRunningProcess(nullptr);

	}
	else if (r >= 5 && r <= 60)
	{
		P_Scheduler->AddToTRM(RunningProcess);
		SetRunningProcess(nullptr);
	}
}
