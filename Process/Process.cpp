#include "Process.h"

Process::Process()
{
	Total_IO_D=NUM_IO = 0;
	AT = TT = TRT = WT = PID = CT = RT = 0;
	RemainingTime = 0;
	DeadLine = 0;
	TimeToReadyBack = -1;
	Parent = LChild = nullptr;
	RChild = nullptr;
	IsChild = false;
}
Process::Process(int at, int pid, int ct, int num_io, int deadline)
{
	AT = at;
	PID = pid;
	CT = ct;
	NUM_IO = num_io;
	DeadLine = deadline;
	Parent = LChild = nullptr;
	RChild = nullptr;
	IsChild = false;
	TimeToReadyBack = -1;
	RemainingTime = ct;
	Total_IO_D = TT = TRT = WT = RT = 0;

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
	TRT = TT - AT;
	WT = TRT - CT;
}




void Process::DecreaseRemainingTime()
{
	RemainingTime--;
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
int Process::getdeadline()
{
	return DeadLine;
}
bool Process::getIsChild()
{
	return IsChild;
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
	if (IO.peek(p))
		TimeToReadyBack = n + p->Second;
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


bool Process::operator >( Process p2)
{
	if (RemainingTime > p2.RemainingTime)
		return true;
	return false;
}

bool Process::operator<(Process p2)
{
	if (DeadLine < p2.DeadLine)
		return true;
	return false;
}

bool Process::operator!=(Process P2)
{
	if (AT != P2.AT)
		return true;
	return false;
}