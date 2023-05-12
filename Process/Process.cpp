#include "Process.h"

Process::Process()
{
	NUM_IO = 0;
	AT = TT = TRT = WT = PID = CT = RT = 0;
	RemainingTime = 0;
	TimeToReadyBack = -1;
	LChild = nullptr;
	RChild = nullptr;
}
Process::Process(int AT, int PID, int CT)
{
	SetAT(AT);
	SetPID(PID);
	SetCT(CT);
	LChild = nullptr;
	RChild = nullptr;
	IsChild = false;
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
void Process::SetIsChild()
{
	IsChild = true;
}
void Process::SetLChild(Process* P)
{
	LChild = P;
}
void Process::SetRChild(Process* P)
{
	RChild = P;
}
void Process::SetParent(Process* P)
{
	Parent = P;
}

void Process::setPair(int first, int second)
{
	Pair* p = new Pair;
	p->First = first;
	p->Second = second;
	Total_IO_D += second;
	IO.enqueue(p);
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


void Process::DecreaseRemainingTime()
{
	RemainingTime--;
}

void Process::PrintID()
{
	std::cout << PID;
}
bool Process::getIsChild()
{
	return IsChild;
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
	
	return Total_IO_D;
}
int Process::getWT()
{
	return WT;
}
int Process::getRT()
{
	return RT;
}
Process* Process::getLChild()
{
	return LChild;
}
Process* Process::getRChild()
{
	return RChild;
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


Process::~Process()
{

}

bool Process::blk_request(int timestep)  
{
	Pair* p = new Pair;
	IO.peek(p);

	if (p->First == timestep)
		return true;
	return false;
}

void Process::Set_TimeToReadyBack(int n)
{
	Pair* p;
	if(IO.peek(p))
		TimeToReadyBack = n+p->Second;
}

int Process::Get_TimeToReadyBack()
{
	return TimeToReadyBack;
}

void Process::PopFirstIO()
{
	Pair* p;
	IO.dequeue(p);
	delete p;
}

std::ostream& operator<<(std::ostream& out, Process* p)
{
	out << p->PID;
	return out;
}


bool operator >(Process p1, Process p2)
{
	if (p1.RemainingTime > p2.RemainingTime)
		return true;
	return false;
}

bool operator!=(Process P1, Process P2)
{
	if (P1.AT != P2.AT)
		return true;
	return false;
}