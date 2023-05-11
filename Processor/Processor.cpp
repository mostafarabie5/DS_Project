#include "Processor.h"

Processor::Processor()
{
	RunningProcess = nullptr;
	Total_Busy = Total_TRT = Total_Idle = PLoad = PUtil = TimetoFinish = 0;
	StopMode = false;
	ActiveAtTime = 0;
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

float Processor::CalcPLoad()
{
	return (float(Total_Busy) / Total_TRT)*100;
}

float Processor::CalcPUtil()
{
	SetTotal_Idle();
	return (float(Total_Busy) / (Total_TRT + Total_Idle))*100;
}



bool Processor::ProcessorState() const
{
	if (RunningProcess)
		return true;
	return false;
}
void Processor::increase_Total_Busy(int x)
{
	Total_Busy += x;
}

void Processor::AddTo_Total_TRT(int x)
{
	Total_TRT += x;

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
}

void Processor::SetTotal_Idle()
{
	Total_Idle = P_Scheduler->GetTimeStep() - Total_Busy;
}

bool Processor::MoveToTRM()
{
	if (RunningProcess->getRemainingTime() == 0)
	{
		P_Scheduler->AddToTRM(RunningProcess);
		Total_TRT += RunningProcess->getTRT();
		RunningProcess = nullptr;
		return true;
	}
	return false;
}

void Processor::set_StopMode(bool b)
{
	StopMode = b;
}

bool Processor::get_StopMode()
{
	return StopMode;
}

void Processor::set_ActiveAtTime(int n)
{
	ActiveAtTime = n;
}

int Processor::get_ActiveAtTime()
{
	return ActiveAtTime;
}


