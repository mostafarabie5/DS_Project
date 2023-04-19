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

	if (RunningProcess)
	{
		if (RunningProcess->getRemainingTime() == 0)
		{
			P_Scheduler->AddToTRM(RunningProcess);
			if (!ReadyList.isEmpty())
			{
				AddToRun();
				/*Run();*////test
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
			else
			{
				return;
			}
		
		
	}
}

void FCFS::AddToReady(Process* P)
{
	ReadyList.InsertEnd(P);
}

void FCFS::PrintReady()
{


	std::cout << "Processor " << ProcessorNumber << " [FCFS]: ";
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
		ReadyList.remove(1);
		SetRunningProcess(ptr);
	}
}

void FCFS::Run()
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
	else if (r >= 50 && r <= 60)
	{
		P_Scheduler->AddToTRM(RunningProcess);
		SetRunningProcess(nullptr);
	}
}

bool FCFS::KILLP(int RandNum)
{
	 
	int x = 1;        /// to get the number of the node that has this pid
	int pid = RandNum;
	if (RunningProcess)
	{
		if (RunningProcess->getPID() == pid)
		{
			P_Scheduler->AddToTRM(RunningProcess);
			SetRunningProcess(nullptr);
			return true;
		}
	}
	Process* pp;
	while (x <= ReadyList.getLength())
	{
		pp = ReadyList.getEntry(x);
		if (pp->getPID() == pid)
		{
			P_Scheduler->AddToTRM(pp);
			ReadyList.remove(x);
			return true;
		}
		x++;
	}
	return false;

}

