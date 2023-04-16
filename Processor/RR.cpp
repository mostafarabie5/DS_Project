#include "RR.h"

RR::RR (int num)
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
