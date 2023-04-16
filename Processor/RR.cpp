#include "RR.h"

RR::RR(int num)
{
	ProcessorNumber = num;
}

void RR::SchedulerAlgo()
{
}

void RR::AddToReady(Process* P)
{
	ReadyQueue.enqueue(P);
}

void RR::PrintReady()
{

	std::cout << "Processor " << ProcessorNumber << " [RR]: ";
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
		Process* ptr;
		ReadyQueue.dequeue(ptr);
		SetRunningProcess(ptr);
	}
}

void RR::Run()
{
	srand(time(0));
	int r = rand() % 100 + 1;
	if (r >= 1 && r <= 15)
		P_Scheduler->AddToBLK(RunningProcess);
	else if (r >= 20 && r <= 30)
		AddToReady(RunningProcess);
	else if (r >= 5 && r <= 60)
		P_Scheduler->AddToTRM(RunningProcess);
	SetRunningProcess(nullptr);
}
