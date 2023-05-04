#include "Processor.h"

Processor::Processor()
{
	RunningProcess = nullptr;
	Total_Busy = Total_TRT = Total_Idle = PLoad = PUtil = TimetoFinish = 0;
}

Processor::Processor(Scheduler* P) :P_Scheduler(P)
{
	RunningProcess = nullptr;
	Total_Busy = Total_TRT = Total_Idle = PLoad = PUtil = TimetoFinish = 0;
}

int Processor::getProcessorNumber(int index)
{
	return ProcessorNumber;
}

int Processor::GetBusyTime()
{
	return Total_Busy;
}

int Processor::CalcPLoad()
{
	return Total_Busy / Total_TRT;
}

int Processor::CalcPutil()
{
	return Total_Busy / (Total_TRT + Total_Idle);
}

bool Processor::ProcessorState() const
{
	if (RunningProcess)
		return true;
	return false;
}

int Processor::GetTimetoFinish()
{
	return TimetoFinish;
}

Process* Processor::getRunningProcess() const
{
	return RunningProcess;
}

void Processor::SetRunningProcess(Process* p)
{
	RunningProcess = p;
	if (p)
		p->SetTransition(P_Scheduler->GetTimeStep());
}


