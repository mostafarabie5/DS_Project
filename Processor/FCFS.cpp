#include "FCFS.h"

FCFS::FCFS( int num) 
{
	ProcessorNumber = num;
}


int FCFS::NumRDY()const
{
	return ReadyList.getLength();
}

void FCFS::SchedulerAlgo()
{
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
