#include "Processor.h"
//---------------------------------(default constructor )----------------------------------------//
Processor::Processor()
{
	RunningProcess = nullptr;
	Total_Busy = Total_TRT = Total_Idle = PLoad = PUtil = TimetoFinish = 0;
	StopMode = false;
	ActiveAtTime = 0;
}
//------------------------------------------(non default constructor )-------------------------------//
Processor::Processor(Scheduler* P) :P_Scheduler(P)
{
	RunningProcess = nullptr;
	Total_Busy = Total_TRT = Total_Idle = PLoad = PUtil = TimetoFinish = 0;
}
//----------------------------------(setter functions)---------------------------------------//
void Processor::SetRunningProcess(Process* p)
{
	RunningProcess = p;
}

void Processor::set_StopMode(bool b)
{
	StopMode = b;
}
void Processor::set_ActiveAtTime(int n)
{
	ActiveAtTime = n;
}
void Processor::SetTotal_Idle()
{
	Total_Idle = P_Scheduler->GetTimeStep() - Total_Busy;
}
//-------------------------------------(Getter functions)------------------------------------//
bool Processor::get_StopMode()const
{
	return StopMode;
}
int Processor::get_ActiveAtTime()const
{
	return ActiveAtTime;
}
int Processor::GetTimetoFinish()const
{
	return TimetoFinish;

}
Process* Processor::getRunningProcess() const
{
	return RunningProcess;
}
//-------------------------------------------------------------------------//
float Processor::CalcPLoad()
{
	PLoad = (float(Total_Busy) / Total_TRT) * 100;
	return PLoad;
}
//-------------------------------------------------------------------------//
float Processor::CalcPUtil()
{
	SetTotal_Idle();
	PUtil = (float(Total_Busy) / (Total_Busy + Total_Idle)) * 100;
	return PUtil;
}

//------------------------------------(return true if busy otherwise return false )-------------------------------------//

bool Processor::ProcessorState() const
{
	if (RunningProcess)
		return true;
	return false;
}

//-------------------------------(return true if th process finished CPU time)------------------------------------------//

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

//-------------------------------------------(search for orphen to be killed )------------------------------------//

void Processor::KillOrphan(Process* p)
{
	if (!p)
		return;
	P_Scheduler->SearchOrphan(p);
	KillOrphan(p->getLChild());
	KillOrphan(p->getRChild());
}

int Processor::Total_TRT;


