#include "FCFS.h"
#include <cstdlib>
#include<ctime>
FCFS::FCFS(Scheduler* sched_ptr, int num) :Processor(sched_ptr)
{
	ProcessorNumber = num;
}

//-----------------------------------------------------//
int FCFS::NumRDY()const
{
	return ReadyList.getLength();
}

void FCFS::SchedulerAlgo()
{
	int TWT; //total waiting time
	if (!RunningProcess)
	{
		if (!ReadyList.isEmpty())
		{
			Process* P = removeProcess();

			TWT = P_Scheduler->GetTimeStep() - P->getAT() - (P->getCT() - P->getRemainingTime());
			if (TWT > P_Scheduler->GetMAXW() && P_Scheduler->GetNRR() && !P->getIsChild() )
			{
				if (P_Scheduler->MoveToShortest("RR" , P))
				{
					P->SetMigrate_FCFS_RR(true);
					SchedulerAlgo();
				}
				else
				{
					RunningProcess = P;
					RunningProcess->setRT(P_Scheduler->GetTimeStep());
				}
			}
			else
			{
				RunningProcess = P;
				RunningProcess->setRT(P_Scheduler->GetTimeStep());
			}
		}
	}
	else
	{
		Process* Running = RunningProcess;
		Total_Busy++;
		RunningProcess->DecreaseRemainingTime();
		
		if (!MoveToTRM())
		{
			if (RunningProcess->blk_request(RunningProcess->getCT() - RunningProcess->getRemainingTime()))
			{
				P_Scheduler->AddToBLK(RunningProcess);
				RunningProcess = nullptr;
			}
		}
		else
		{
			KillOrphan(Running->getLChild());
			KillOrphan(Running->getRChild());
		}
	}
}

void FCFS::AddToReady(Process* P)
{
	ReadyList.InsertEnd(P);
	TimetoFinish += P->getRemainingTime();
}

void FCFS::PrintReady() const
{
	ReadyList.Print(StopMode);
}

void FCFS::setSIGKILL(int time, int Id)
{
	Pair* p = new Pair;
	p->First = time;
	p->Second = Id;
	SIGKILL.enqueue(p);
}

Process* FCFS::Delete_FirstProcess()
{
	Process* ptr = nullptr;
	int i;
	for (i = 0; i < ReadyList.getLength(); i++)
	{
		ptr = ReadyList.getEntry(i+1);
		if (!ptr->getIsChild())
			break;
	}
	if (i == ReadyList.getLength())
		ptr = nullptr;
	else
	{
		if (ptr) 
		{
			TimetoFinish -= ptr->getRemainingTime();
			ReadyList.remove(i + 1);
		}
	}
	return ptr;
}

bool FCFS::KillProcess()
{
	Pair* Signal;
	bool found=false;
	Process* p = nullptr;
	int Position_ReadyList;
	if (SIGKILL.peek(Signal))
	{
		while (Signal->First < P_Scheduler->GetTimeStep())
		{
			popKillSignal();
			if (!SIGKILL.peek(Signal))
				break;
		}

		if (SIGKILL.peek(Signal))
		{
			if (Signal->First == P_Scheduler->GetTimeStep())
			{
				if (RunningProcess && (RunningProcess->getPID() == Signal->Second))
				{
					P_Scheduler->AddToTRM(RunningProcess);
					p = RunningProcess;
					RunningProcess = nullptr;
					found = true;
				}
				else
				{
					for (int i = 1; i <= ReadyList.getLength() && !found; i++)
					{
						p = ReadyList.getEntry(i);
						if (p->getPID() == Signal->Second)
						{
							found = true;
							Position_ReadyList = i;
						}
					}

					if (found)
					{
						P_Scheduler->AddToTRM(p);
						ReadyList.remove(Position_ReadyList);
						TimetoFinish -= p->getRemainingTime();
					}
				}

				if (found)
				{
					p->SetIsKilled(true);
					popKillSignal();
					KillOrphan(p->getLChild());
					KillOrphan(p->getRChild());
					if (SIGKILL.peek(Signal))
						if (Signal->First == P_Scheduler->GetTimeStep())
							P_Scheduler->KillFCFS_Process();
				}
			}
		}
	}
	return found;
}

bool FCFS::OrphanPosition(Process*& p)
{
	bool found = false;
	int position;
	Process* temp;
	if (RunningProcess == p)
	{
		p->SetIsKilled(true);
		P_Scheduler->AddToTRM(RunningProcess);
		RunningProcess = nullptr;
		return true;
	}
	
	for (int i = 1; i <= ReadyList.getLength() && !found; i++)
	{
		temp = ReadyList.getEntry(i);
		if (p->getPID() == temp->getPID())
		{
			found = true;
			position = i;
		}
	}
	if (found)
	{
		p->SetIsKilled(true);
		P_Scheduler->AddToTRM(p);
		ReadyList.remove(position);
		TimetoFinish -= p->getRemainingTime();
	}
	
	
	return found;
}

void FCFS::popKillSignal()
{
	Pair* p;
	if (!SIGKILL.isEmpty())
	{
		SIGKILL.dequeue(p);
		delete p;
	}
}

bool FCFS::Ready_isEmpty() const
{
	return ReadyList.isEmpty();
}

void FCFS::AddForkedProcess()
{
	int RandomNum = rand() % 100;
	if (RandomNum < P_Scheduler->getForkProbabilty() && RunningProcess && (!RunningProcess->getLChild() || !RunningProcess->getRChild()))
	{
		RunningProcess->SetIsForked(true);

		int pid = P_Scheduler->GetNP() + 1;
		P_Scheduler->SetNP(pid);
		Process* ptr = new Process(P_Scheduler->GetTimeStep(), pid, RunningProcess->getRemainingTime());
		ptr->SetIsChild();
		ptr->SetParent(RunningProcess);

		if (!RunningProcess->getLChild())
		{
			RunningProcess->SetLChild(ptr);
			P_Scheduler->MoveToShortest("FCFS", ptr);
		}
		else
		{
			RunningProcess->SetRChild(ptr);
			P_Scheduler->MoveToShortest("FCFS", ptr);
		}
	}
	
}

Process* FCFS::removeProcess()
{
	Process* ptr;
	ptr = ReadyList.getEntry(1);
	ReadyList.remove(1);
	TimetoFinish -= ptr->getRemainingTime();
	return ptr;
}

FCFS::~FCFS()
{
}

Queue<Pair*> FCFS::SIGKILL;
