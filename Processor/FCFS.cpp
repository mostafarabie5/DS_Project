#include "FCFS.h"
#include <cstdlib>
#include<ctime>
FCFS::FCFS(Scheduler * sched_ptr,int num):Processor(sched_ptr)
{
	ProcessorNumber = num;
}


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
			Process* P;
			P = Delete_FirstProcess();
			SetRunningProcess(P);
		}
	}
	else
	{
		Total_Busy++;
		RunningProcess->DecreaseRemainingTime();
		TWT = P_Scheduler->GetTimeStep() - RunningProcess->getAT() - (RunningProcess->getCT() - RunningProcess->getRemainingTime());
		if (!MoveToTRM())
		{
			if (RunningProcess->blk_request(RunningProcess->getCT() - RunningProcess->getRemainingTime()))
			{
				P_Scheduler->AddToBLK(RunningProcess);
				RunningProcess = nullptr;
				return;
			}
		}
		else
		{
			return;
		}
		////////////////////////////////////////// forking 
		int RandomNum = rand() % 100;
		if (RandomNum < 10&&(!RunningProcess->getLChild() || !RunningProcess->getRChild()))
		{
				int pid = P_Scheduler->GetNP() + 1;
				P_Scheduler->SetNP(pid);
				Process* ptr =  new Process(P_Scheduler->GetTimeStep(), pid, RunningProcess->getRemainingTime());
				ptr->SetIsChild();
				ptr->SetParent(RunningProcess);
				
				if (!RunningProcess->getLChild())
				{
					RunningProcess->SetLChild(ptr);
					P_Scheduler->MoveToShortest(ptr, P_Scheduler->GetNFCFS());
					if (!RunningProcess->getIsChild())
					{
						P_Scheduler->MoveToShortest(RunningProcess, P_Scheduler->GetPP());
						
					}
					else
					{
						P_Scheduler->MoveToShortest(RunningProcess, P_Scheduler->GetNFCFS());
					}
					SetRunningProcess(nullptr);
				}
				else
				{
					RunningProcess->SetRChild(ptr);
					P_Scheduler->MoveToShortest(ptr, P_Scheduler->GetNFCFS());
					if (!RunningProcess->getIsChild())
					{
						P_Scheduler->MoveToShortest(RunningProcess, P_Scheduler->GetPP());

					}
					else
					{
						P_Scheduler->MoveToShortest(RunningProcess, P_Scheduler->GetNFCFS());
					}
					SetRunningProcess(nullptr);
				}
		}
		////////////////////////////////////////////////
		if (TWT > P_Scheduler->GetMAXW()&&RunningProcess)
		{
			P_Scheduler->MoveToShortest(RunningProcess, P_Scheduler->GetNRR());
			SetRunningProcess(nullptr);
		}
	}
}

void FCFS::AddToReady(Process* P)
{
	ReadyList.InsertEnd(P);
	TimetoFinish += P->getRemainingTime();
}

void FCFS::PrintReady()
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
	Process* ptr = ReadyList.getEntry(1);
	ReadyList.remove(1);
	TimetoFinish -= ptr->getRemainingTime();
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
			SIGKILL.dequeue(Signal);
			delete Signal;
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
					KillOrphan(RunningProcess->getLChild());
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
						TimetoFinish -= p->getCT();
						KillOrphan(p->getLChild());
					}
				}
				if (found)
				{
					SIGKILL.dequeue(Signal);
					delete Signal;
					if (SIGKILL.peek(Signal))
						if (Signal->First == P_Scheduler->GetTimeStep())
							P_Scheduler->KillFCFS_Process();
				}
			}
		}
		
	}
	return found;
}

void FCFS::KillOrphan(Process* p)
{
	if (!p)
		return;
	P_Scheduler->SearchOrphan(p);
	KillOrphan(p->getLChild());
}

bool FCFS::OrphanPosition(Process*& p)
{
	bool found = false;
	int position;
	Process* temp;
	if (RunningProcess == p)
	{
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
		P_Scheduler->AddToTRM(p);
		ReadyList.remove(position);
		TimetoFinish -= p->getCT();
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

bool FCFS::Ready_isEmpty()
{
	return ReadyList.isEmpty();
}


Queue<Pair*> FCFS::SIGKILL;
