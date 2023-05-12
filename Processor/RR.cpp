#include "RR.h"

RR::RR(Scheduler*sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
	count = 0;
}

void RR::SchedulerAlgo()
{
	if (RunningProcess)
	{
		Total_Busy++;
		count++;
		RunningProcess->DecreaseRemainingTime();
		if (!MoveToTRM())
		{
			if (RunningProcess->blk_request(RunningProcess->getCT() - RunningProcess->getRemainingTime()))
			{
				P_Scheduler->AddToBLK(RunningProcess);
				SetRunningProcess(nullptr);
				count = 0;
				return;
			}
		}
		else
		{
			count = 0;
			return;
		}
		if (RunningProcess->getRemainingTime() < P_Scheduler->GetRTF())
		{
			P_Scheduler->MoveToShortest(RunningProcess, P_Scheduler->GetNSJF());
			count = 0;
			SetRunningProcess(nullptr);
		}
		if (count == P_Scheduler->GetTS())
		{
			P_Scheduler->MoveToShortest(RunningProcess, P_Scheduler->GetPP());
			count = 0;
			SetRunningProcess(nullptr);
		}
		

	}
	else
	{
		if (!ReadyQueue.isEmpty())
		{
			Process* ptr;
			ptr = Delete_FirstProcess();
			SetRunningProcess(ptr);
			ptr->setRT(P_Scheduler->GetTimeStep());
		}
	}

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

