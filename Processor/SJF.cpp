#include "SJF.h"

SJF::SJF(Scheduler* sched_ptr, int num) :Processor(sched_ptr)
{
	ProcessorNumber = num;
}

void SJF::SchedulerAlgo()
{
	if (RunningProcess)
	{
		Process* Running = RunningProcess;

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
		else
		{
			KillOrphan(Running->getLChild());
			KillOrphan(Running->getRChild());
		}
	}
	else {

		if (!ReadyList.isEmpty())
		{
			Process* ptr = Delete_FirstProcess();
			SetRunningProcess(ptr);
			ptr->setRT(P_Scheduler->GetTimeStep());
		}
	}

}
//--------------------------------------------------------------//
void SJF::AddToReady(Process* P)
{
	TimetoFinish = TimetoFinish+P->getRemainingTime();
	ReadyList.add(P);
}
//-----------------------------------------------------------//
void SJF::PrintReady()
{
	ReadyList.Print(StopMode);
}
//--------------------------------------------------------//
int SJF::NumRDY() const
{
	return ReadyList.getLength();
}
//-----------------------------------------------------//


Process* SJF::Delete_FirstProcess()
{

	Process* ptr;
	ptr = ReadyList.peek();
	ReadyList.remove(1);
	TimetoFinish -= ptr->getRemainingTime();
	return ptr;
}

bool SJF::Ready_isEmpty()
{
	return ReadyList.isEmpty();
}


