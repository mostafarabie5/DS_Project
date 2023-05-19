#include "Process.h"

Process::Process()
{
	Total_IO_D = NUM_IO = 0;
	AT = TT = TRT = WT = PID = CT = RT = 0;
	RemainingTime = 0;
	DeadLine = 0;
	TimeToReadyBack = -1;
	Parent = LChild = nullptr;
	RChild = nullptr;
	IsChild = false;

	Steal = false;
	Migrate_FCFS_RR = false;
	Migrate_RR_SJF = false;
	IsForked = false;
	IsKilled = false;
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
	Steal = false;
	Migrate_FCFS_RR = false;
	Migrate_RR_SJF = false;
	IsForked = false;
	IsKilled = false;

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
	WT = TRT - (CT - RemainingTime);
}




void Process::DecreaseRemainingTime()
{
	RemainingTime--;
}


int Process::getAT() const
{
	return AT;
}

int Process::getCT() const
{
	return CT;
}
int Process::getPID() const
{
	return PID;
}
int Process::getTT() const
{
	return TT;
}
int Process::getTRT() const
{
	return TRT;
}
int Process::get_Total_IO_D() const
{

	return Total_IO_D;
}
int Process::getWT() const
{
	return WT;
}
int Process::getRT() const
{
	return RT;
}
Process* Process::getLChild() const
{
	return LChild;
}
Process* Process::getRChild() const
{
	return RChild;
}

int Process::getRemainingTime() const
{
	return RemainingTime;
}
int Process::getdeadline() const
{
	return DeadLine;
}
bool Process::getIsChild() const
{
	return IsChild;
}
int Process::getParentID() const
{
	return Parent->PID;
}
void  Process::setRT(int x)
{
	if (RT == 0)
		RT = x;
}


bool Process::blk_request(int timestep) const
{
	Pair* p = new Pair;
	if (IO.peek(p))
	{
		if (p->First == timestep)
			return true;
	}
	return false;
}

void Process::Set_TimeToReadyBack(int n)
{
	Pair* p;
	if (IO.peek(p))
		TimeToReadyBack = n + p->Second;
}

int Process::Get_TimeToReadyBack() const
{
	return TimeToReadyBack;
}


void Process::PopFirstIO()
{
	Pair* p;
	IO.dequeue(p);
	delete p;
}

void Process::Setsteal(bool n)
{
	Steal = n;
}

bool Process::Getsteal() const
{
	return Steal;
}

void Process::SetIsKilled(bool n)
{
	IsKilled = n;
}

bool Process::GetIsKilled() const
{
	return IsKilled;
}

void Process::SetMigrate_RR_SJF(bool n)
{
	Migrate_RR_SJF = n;
}

void Process::SetMigrate_FCFS_RR(bool n)
{
	Migrate_FCFS_RR = n;
}

bool Process::GetMigrate_RR_SJF() const
{
	return Migrate_RR_SJF;
}

void Process::SetIsForked(bool n)
{
	IsForked = n;
}

bool Process::GetIsForked() const
{
	return IsForked;
}

bool Process::GetMigrate_FCFS_RR() const
{
	return Migrate_FCFS_RR;
}

std::ostream& operator<<(std::ostream& out, Process* p)
{
	out << p->PID;
	return out;
}


bool Process::operator >(Process p2)
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
Process::~Process()
{
}