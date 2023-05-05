#include "Process.h"

Process::Process()
{
	NUM_IO = 0;
	AT = TT = TRT = WT = PID = CT = RT = 0;
	RemainingTime = 0;
	child = nullptr;
	TransitionTime = -1;
}
Process::Process(int AT, int PID, int CT, IO_requests* io)
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

void Process::SetTT(int x)
{
	TT = x;
	SetTRT();
	SetWT();
}

void Process::SetTRT()
{
	TRT = TT - AT;
}

void Process::SetWT()
{
	WT = TRT - CT;
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
int Process::getTT()
{
	return TT;
}
int Process::getTRT()
{
	return TRT;
}
int Process::get_Total_IO_D()
{
	int sum = 0;
	for (int i = 0;i < NUM_IO;i++)
	{
		sum += IO[i].IO_D;
	}
	return sum;
}
int Process::getWT()
{
	return WT;
}
int Process::getRT()
{
	return RT;
}
int Process::getRemainingTime()
{
	return RemainingTime;
}

void  Process::setRT(int x)
{
	if (RT == 0)
		RT = x;
}

int Process::getio_d()
{
	for (int i = 0;i < NUM_IO;i++)
	{
		if (IO[i].IO_R == CT-RemainingTime)
			return IO[i].IO_D;
	}
}

Process::~Process()
{

}

bool Process::blk_request(int timestep)
{
	for (int i = 0;i < NUM_IO;i++)
		if (IO[i].IO_R == timestep)
			return true;
	return false;
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