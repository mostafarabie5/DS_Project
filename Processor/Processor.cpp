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

int Processor::CalcPLoad()
{
	return Total_Busy / Total_TRT;
}

int Processor::CalcPutil()
{
	return Total_Busy / (Total_TRT + Total_Idle);
}

void Processor::AddToRun(Process* P)
{
	RunningProcess = P;
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

void Processor::PrintRunningProcess() const
{
	RunningProcess->Print();
	std::cout << "(P" << ProcessorNumber << "), ";
}


