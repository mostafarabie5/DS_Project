#include "RR.h"

RR::RR(Scheduler*sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
}

void RR::SchedulerAlgo()
{
	/*if (RunningProcess)
	{
		Run();
	}
	else
	{
		if (!ReadyQueue.isEmpty())
		{
			AddToRun();
		}
	}*/

}

void RR::AddToReady(Process* P)
{
	TimetoFinish += P->getRemainingTime();
	ReadyQueue.enqueue(P);
}

void RR::PrintReady()
{
	ReadyQueue.Print(NumRDY(), " RDY: ",StopMode);
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


		ReadyQueue.dequeue(ptr);
		SetRunningProcess(ptr);
		TimetoFinish -= ptr->getCT();
	}
}


Process* RR::Delete_FirstProcess()
{
	Process* ptr = nullptr;
	ReadyQueue.dequeue(ptr);
	TimetoFinish -= ptr->getRemainingTime();
	return ptr;
}

bool RR::Ready_isEmpty()
{
	return ReadyQueue.isEmpty();
}

