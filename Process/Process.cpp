#include "Process.h"

Process::Process()
{
	NUM_IO = 0;
	AT = TT = TRT = WT = PID = CT = RT = 0;
	RemainingTime = 0;
	child = nullptr;
}
Process::Process(int AT, int PID, int CT, Queue<Pair> IO_Time)
{
	SetAT(AT);
	SetPID(PID);
	SetCT(CT);
	IO = IO_Time;
	child = nullptr;
}
void Process::SetAT(int at)
{
	AT = at;
}
void Process::SetCT(int ct)
{
	CT = ct;
}
void Process::SetPID(int id)
{
	PID = id;
}
void Process::SetNUM_IO(int n)
{
	NUM_IO = n;
}

void Process::setPair(int first, int second)
{
	Pair p;
	p.setFirst(first);
	p.setSecond(second);
	IO.enqueue(p);
}

void Process::Print()
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

Process::~Process()
{

}


std::ostream& operator<<(std::ostream& out, Process p)
{
	p.Print();
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