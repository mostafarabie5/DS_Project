#include "SJF.h"

SJF::SJF( int num)
{
	ProcessorNumber = num;
}

void SJF::SchedulerAlgo()
{
}

void SJF::AddToReady(Process* P)
{
	ReadyList.add(P);
}

void SJF::PrintReady()
{
	std::cout << "Processor " << ProcessorNumber << " [SJF]: ";
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
