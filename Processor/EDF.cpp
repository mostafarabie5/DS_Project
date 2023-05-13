#include "EDF.h"

EDF::EDF(Scheduler* sched_ptr, int num) :Processor(sched_ptr)
{
	ProcessorNumber = num;
}
//-----------------------------------------------------//
void EDF::SchedulerAlgo()
{

	if (RunningProcess)
	{
		if (!ReadyList.isEmpty()&&RunningProcess->getdeadline() > ReadyList.peek()->getdeadline())
		{
			AddToReady(RunningProcess);
			RunningProcess = nullptr;
			AddToRun();

		}

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

		AddToRun();
	}
}
//-----------------------------------------------------//
void EDF::AddToReady(Process* P)
{
	TimetoFinish = TimetoFinish + P->getRemainingTime();
	ReadyList.add2(P);
}
//-----------------------------------------------------//
void EDF::PrintReady()
{
	ReadyList.Print(StopMode);
}
//-----------------------------------------------------//
int EDF::NumRDY() const
{
	return ReadyList.getLength();

}
//-----------------------------------------------------//
void EDF::AddToRun()
{
	if (!ReadyList.isEmpty())
	{
		Process* ptr = Delete_FirstProcess();
		SetRunningProcess(ptr);
		ptr->setRT(P_Scheduler->GetTimeStep());

	}
}
//-----------------------------------------------------//
Process* EDF::Delete_FirstProcess()
{
	Process* ptr;
	ptr = ReadyList.peek();
	ReadyList.remove(1);
	TimetoFinish -= ptr->getRemainingTime();
	return ptr;
}

bool EDF::Ready_isEmpty()
{
	return ReadyList.isEmpty();
}
