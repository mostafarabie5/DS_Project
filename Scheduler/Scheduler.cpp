#include "Scheduler.h"
#include<iostream>

Scheduler::Scheduler()
{

}

void Scheduler::Load(string FileName)
{
	Infile.open(FileName + ".txt", ios::in);
	int nf,ns,nr;
	Infile >> nf>>ns>>nr;
	SetNFCFS(nf);
	SetNSJF(ns);
	SetNRR(nr);
	SetP_Processor();
	int ts;
	Infile >> ts;
	SetTS(ts);
	Infile >> RTF >> MAXW >> STL >> fork;
	int np;
	Infile >>np ;
	SetNP(np);
	for (int i = 0; i < NP; i++)
	{
		int AT, PID, CT, NUM_IO;
		Infile >> AT >> PID >> CT >> NUM_IO;
		Process* ptr = new Process;
		ptr->SetAT(AT);
		ptr->SetCT(CT);
		ptr->SetNUM_IO(NUM_IO);
		ptr->SetPID(PID);
		for (int j = 0; j < NUM_IO;j++)
		{
			int first, second;
			char c;
			Infile >> c >> first >> c >> second >> c;
			ptr->setPair(first, second);
			if (j != NUM_IO - 1)
				Infile >> c;
		}
		NEW.enqueue(ptr);
	}
	while (!Infile.eof())
	{
		int first, second;
		Infile >> first >> second;
		Pair p;
		p.setFirst(first);
		p.setSecond(second);
		SIGKILL.enqueue(p);
	}
	Infile.close();
}

void Scheduler::SetNFCFS(int n)
{
	NFCFS = n;
	
}

void Scheduler::SetNSJF(int n)
{
	NSJF = n;
	
}

void Scheduler::SetNRR(int n)
{
	NRR = n;
}

void Scheduler::SetNP(int n)
{
	NP = n;
}


void Scheduler::SetTS(int t)
{
	TS = t;
}

void Scheduler::SetP_Processor()
{
	int n = NFCFS + NSJF + NRR;
	SetPP(n);
	P_Processor = new Processor * [n];
	int i = 0;
	for (;i < NFCFS;i++)
	{
		P_Processor[i] = new FCFS(this, i+1);
	}
	for (;i < NFCFS + NSJF;i++)
	{
		P_Processor[i] = new SJF(this, i+1);
	}
	for (;i < n;i++)
	{
		P_Processor[i] = new RR(this, i+1);
	}
}

void Scheduler::AddToNEW(Process* P)
{
	NEW.enqueue(P);
}

void Scheduler::AddToBLK(Process* P)
{
	BLK.enqueue(P);
}

void Scheduler::AddToTRM(Process* P)
{
	TRM.enqueue(P);
}

void Scheduler::SetPP(int n)
{
	PP = n;
}

int Scheduler::ShorestQueue()
{
	return 1;
}

int Scheduler::LongestQueue()
{
	return 1;
}

void Scheduler::CalcStealLimit()
{
	int StealLimit = (LongestQueue() - ShorestQueue()) / LongestQueue();

	if (StealLimit > 40)
	{
		/////   should pop a Process from the longest and push it in the shorteast and do that until the StealLimit be smaller than 40
	}
}

void Scheduler::PassProcessTo(Process* P)
{
	//ADD process to the shortest queue
}

void Scheduler::CreatNewPro(int T, int ct)  ///for forking 
{
	/*Process* P = new Process;
	P->SetPID();/// unique
	P->SetAT(T);
	P->SetCT(ct);*/
	/// should enqeue ii in the ready list of FCFS

}

void Scheduler::Print()
{
	//UIPtr->UpdateInterface(this);

}

int Scheduler::GetNFCFS() const
{
	return NFCFS;
}

int Scheduler::GetNSJF() const
{
	return  NSJF;
}

int Scheduler::GetNRR() const
{
	return NRR;
}
int Scheduler::GetTS() const
{
	return TS;
}
void Scheduler::Simulate()
{
	int i = 0;
	string s = ReadFileName();
	Load(s);
	int num = NFCFS + NSJF + NRR;
	Process* p;
	int time = 1;
	if (!NEW.isEmpty())
	{
		NEW.dequeue(p);
	}
	else
	{
		p = nullptr;
		UIPtr->UpdateInterface(this);
		return;

	}
	while (NP != TRM.Getcount())
	{
		if (p)
		{
			while (p->getAT() == time)
			{
				i = i % num;

				P_Processor[i]->AddToReady(p);

				if (!NEW.isEmpty())
				{
					NEW.dequeue(p);
					i++;
				}
				else
				{
					p = nullptr;
					break;
				}

			}
		}


		bool killx = false;
		int RandNum = rand() % 30 + 1;  ///randnum
		for (int j = 0; j < NFCFS; j++)
		{
			if (!killx)
			{
				killx = ((FCFS*)P_Processor[j])->KILLP(RandNum);
			}

			P_Processor[j]->SchedulerAlgo();

		}
		for (int j = NFCFS; j < num; j++)
		{


			P_Processor[j]->SchedulerAlgo();

		}
		Process* temp;
		if (!BLK.isEmpty())
		{
			i = i % num;
			int r = rand() % 100 + 1;
			if (r >= 1 && r <= 10)
			{
				BLK.dequeue(temp);
				if (!P_Processor[i]->ProcessorState())
				{
					P_Processor[i]->SetRunningProcess(temp);
				}
				else
				{
					P_Processor[i]->AddToReady(temp);
				}
				i++;
			}
		}
		UIPtr->UpdateInterface(this);
		char ch;
		cin >> ch;
		time++;
	}
}


int Scheduler::RunningProcessors() const
{
	int count = 0;
	for (int i = 0; i < PP; i++)
	{
		if (P_Processor[i]->ProcessorState())
			count++;
	}
	return count;
}

void Scheduler::PrintProcessor()
{
	for (int i = 0; i < PP; i++)
	{
		P_Processor[i]->PrintReady();
	}
	//// loop to print one processor of each type 
}

void Scheduler::PrintBLK()
{
	BLK.Print(BLK.Getcount(), " BLK: ");
}

void Scheduler::PrintTRM()
{
	TRM.Print(TRM.Getcount(), " TRM: ");
}

void Scheduler::PrintRUN()
{

	for (int i = 0;i < PP;i++)
	{
		if (P_Processor[i]->ProcessorState())
			P_Processor[i]->PrintRunningProcess();
	}
}

string Scheduler::ReadFileName()
{
	string m;
	cin >> m;
	return string(m);
}
