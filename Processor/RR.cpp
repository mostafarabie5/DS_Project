#include "RR.h"

RR::RR(Scheduler* sched_ptr, int num) :Processor(sched_ptr)
{
	ProcessorNumber = num;
	count = 0;
}
//---------------------------------------------------------------//
void RR::SchedulerAlgo()
{
	if (RunningProcess)
	{
		Process* Running = RunningProcess;
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
			KillOrphan(Running->getLChild());
			KillOrphan(Running->getRChild());
			count = 0;
			return;
		}
		if (count == P_Scheduler->GetTS())
		{
			AddToReady(RunningProcess);
			count = 0;
			RunningProcess = nullptr;
		}


	}
	else
	{
		bool x = false;
		while (!x && !ReadyQueue.isEmpty())
		{
			Process* ptr;
			ptr = Delete_FirstProcess();
			if (ptr->getRemainingTime() < P_Scheduler->GetRTF() && P_Scheduler->GetNSJF())
			{
				if (!P_Scheduler->MoveToShortest("SJF", ptr))
				{
					RunningProcess = ptr;
					ptr->setRT(P_Scheduler->GetTimeStep());
					x = true;
				}
				else
					ptr->SetMigrate_RR_SJF(true);
				count = 0;
			}
			else
			{
				RunningProcess = ptr;
				ptr->setRT(P_Scheduler->GetTimeStep());
				x = true;
			}

		}
	}

}
//-----------------------------------------------------//
void RR::AddToReady(Process* P)
{
	TimetoFinish += P->getRemainingTime();
	ReadyQueue.enqueue(P);
}
//-----------------------------------------------------//
void RR::PrintReady()const
{
	ReadyQueue.Print(NumRDY(), " RDY: ", StopMode);
}

//-----------------------------------------------------//
int RR::NumRDY() const
{
	return ReadyQueue.Getcount();
}
//-----------------------------------------------------//
void RR::AddToRun()
{
	if (!ReadyQueue.isEmpty())
	{
		Process* ptr = nullptr;
		ReadyQueue.peek(ptr);


		ReadyQueue.dequeue(ptr);
		SetRunningProcess(ptr);
		TimetoFinish -= ptr->getRemainingTime();
	}
}
//-----------------------------------------------------//


Process* RR::Delete_FirstProcess()
{
	Process* ptr = nullptr;
	ReadyQueue.dequeue(ptr);
	TimetoFinish -= ptr->getRemainingTime();
	return ptr;
}
//-----------------------------------------------------//
bool RR::Ready_isEmpty()const
{
	return ReadyQueue.isEmpty();
}

RR::~RR()
{
}