#include "SJF.h"

SJF::SJF(Scheduler* sched_ptr, int num) :Processor(sched_ptr)
{
	ProcessorNumber = num;
}

void SJF::SchedulerAlgo()
{
	if (RunningProcess)
	{


		Total_Busy++;

		RunningProcess->DecreaseRemainingTime();
		if (!MoveToTRM())
		{
			if (RunningProcess->blk_request(RunningProcess->getCT() - RunningProcess->getRemainingTime()))
			{
				P_Scheduler->AddToBLK(RunningProcess);
				RunningProcess = nullptr;
			}
		}
	}
	else {

		if (!ReadyList.isEmpty())
		{
			Process* ptr;
			ptr = ReadyList.peek();

			ReadyList.remove(1);
			SetRunningProcess(ptr);
			TimetoFinish -= ptr->getCT();
			ptr->setRT(P_Scheduler->GetTimeStep());

		}
	}

}

void SJF::AddToReady(Process* P)
{
	TimetoFinish = TimetoFinish+P->getCT();
	ReadyList.add(P);
}

void SJF::PrintReady()
{
	ReadyList.Print();
}

int SJF::NumRDY() const
{
	return ReadyList.getLength();
}


Process* SJF::Delete_FirstProcess()
{

	Process* ptr;
	ptr = ReadyList.peek();
	ReadyList.remove(1);
	TimetoFinish -= ptr->getCT();
	return ptr;
}


