#include "Process.h"

Process::Process()
{
	NUM_IO = 0;
	AT = TT = TRT = WT = PID = CT = RT = 0;
	RemainingTime = 0;
	child = nullptr;
	TransitionTime = -1;
}
Process::Process(int AT, int PID, int CT,IO_requests* io)
{
	SetAT(AT);
	SetPID(PID);
	SetCT(CT);
	IO = io;
	child = nullptr;
}
void Process::SetAT(int at)
{
	AT = at;
}
void Process::SetCT(int ct)
{
	CT = ct;
	RemainingTime = ct;
}
void Process::SetPID(int id)
{
	PID = id;
}
void Process::SetNUM_IO(int n)
{
	NUM_IO = n;
}

void Process::SetIO(IO_requests* io)
{
	IO = io;
}
void Process::DecreaseRemainingTime()
{
	RemainingTime--;
}

void Process::PrintID()
{
	std::cout << PID;
}

int Process::getAT()
{
	return AT;
}

int Process::getCT()
{
	return CT;
}
int Process::getPID()
{
	return PID;
}
int Process::getRemainingTime()
{
	return RemainingTime;
}

Process::~Process()
{

}


std::ostream& operator<<(std::ostream& out, Process* p)
{
	out << p->PID;
	return out;
}


bool operator >(Process p1, Process p2)
{
	if (p1.CT > p2.CT)
		return true;
	return false;
}

bool operator!=(Process P1, Process P2)
{
	if (P1.AT != P2.AT)
		return true;
	return false;
}