#include "Scheduler.h"
#include<iostream>

Scheduler::Scheduler()
{

}

void Scheduler::Load(string FileName)
{
	Infile.open(FileName + ".txt", ios::in);
	int nf, ns, nr;
	Infile >> nf >> ns >> nr;
	SetNFCFS(nf);
	SetNSJF(ns);
	SetNRR(nr);
	SetP_Processor();
	int ts;
	Infile >> ts;
	SetTS(ts);
	Infile >> RTF >> MAXW >> STL >> fork;
	int np;
	Infile >> np;
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
		for (int j = 0; j < NUM_IO; j++)
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
	while (NFCFS > 0 && !Infile.eof())
	{
		int first, second;
		Infile >> first >> second;
		static_cast<FCFS*>(P_Processor[0])->setSIGKILL(first, second);
	}
	Infile.close();

}

void Scheduler::OP_File()
{
	outfile.open("OutputFile.txt", ios::out);
	outfile << "TT       PID       AT       CT       IO_D       WT       RT       TRT" << endl;
	Process* p;
	for (int i = 0;i < NP;i++)
	{
		TRM.dequeue(p);
		outfile << p->getTT() << "       " << p->getPID() << "        " << p->getAT() << "        " << p->getCT() << "        " << p->get_Total_IO_D() << "        ";
		outfile << p->getWT() <<  "        " << p->getRT() << "        " << p->getTRT();
		outfile << endl;
	}

	outfile << "Processes : " << NP << endl;
	outfile << "AVG WT=" << AVG_WT << "      " << "AVG_RT=" << AVG_RT << "      " << "AVG TRT=" << AVG_TRT << endl;
	outfile << "Migiration%:" << "      " << "RTF=" << RTF << "      " << "MaxW=" << MAXW << "      ";
	outfile << "Work Steal%="  << CalcStealLimit()<< endl;
	outfile << "Forked Processes : " << endl;
	outfile << "killed Proceeses : " << endl;
	outfile << "Processors : " << PP << "[" << NFCFS << " FCFS ," << NSJF << " SJF ," << NRR << " RR ]" << endl;
	outfile << "Procesores load" << endl;
	for (int i = 0;i < PP;i++)
	{
		outfile << "P" << i + 1 << "=" << P_Processor[i]->CalcPLoad();
		outfile << "   ";
	}
	outfile << endl;
	outfile << "Processores Utiliz" << endl;
	float sum = 0;
	for (int i = 0;i < PP;i++)
	{
		sum += P_Processor[i]->CalcPUtil();
		outfile << "P" << i + 1 << "=" << P_Processor[i]->CalcPUtil();
		outfile << "   ";
	}
	outfile << endl;
	outfile << "AVG Utilization=" << sum / PP;
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
		P_Processor[i] = new FCFS(this, i + 1);
	}
	for (;i < NFCFS + NSJF;i++)
	{
		P_Processor[i] = new SJF(this, i + 1);
	}
	for (;i < n;i++)
	{
		P_Processor[i] = new RR(this, i + 1);
	}
}

void Scheduler::AddToNEW(Process* P)
{
	NEW.enqueue(P);
}

void Scheduler::AddToBLK(Process* P)
{
	if (BLK.isEmpty())
		P->Set_TimeToReadyBack(timestep);
	BLK.enqueue(P);
}

void Scheduler::AddToTRM(Process* P)
{

	P->SetTT(timestep);
	AVG_RT = AVG_RT +P->getRT() /float (NP);
	AVG_TRT = AVG_TRT + P->getTRT() / float(NP);
	AVG_WT = AVG_WT +P->getWT() / float(NP);
	TRM.enqueue(P);
}

void Scheduler::SetPP(int n)
{
	PP = n;
}




float Scheduler::CalcStealLimit()
{
	float StealLimit;
	if (LP->NumRDY() == 1 )
		return 0;


	if (LongQueue > 0)
	{
		StealLimit = ((float(LongQueue) - ShortQueue) / LongQueue)*100;
		return StealLimit;
	}
	return 0;
}

void Scheduler::PassProcessTo(Process* P)
{
	//ADD process to the shortest queue
}

void Scheduler::CreatNewPro(int T, int ct)  ///for forking 
{

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
int Scheduler::GetTimeStep() const
{
	return timestep;
}
void Scheduler::Simulate()
{

	int i = 0;
	string s = UIPtr->ReadFileName();
	Load(s);
	int mode;
	mode = UIPtr->ReadMode();
	while (TRM.Getcount() != NP)
	{
		Process* P;
		if (NEW.peek(P))
		{
			while (NEW.peek(P)&&P->getAT() == timestep)
			{
				CalcLStQueue();
				NEW.dequeue(P);
				SP->AddToReady(P);
			}
		}
		BackToReady();

		for (int i = 0;i < PP;i++)
		{
				P_Processor[i]->SchedulerAlgo();
		}
		if (timestep% STL==0)
		{
			CalcLStQueue();
			while (CalcStealLimit()>40)
			{
				Process*P=LP->Delete_FirstProcess();
				SP->AddToReady(P);
			}
		}
		//////////////////////////////////////////////////////////////////
		//from blk to ready
		/////////////////////////////////////////////////////////////////
		for (int i = 0; i < NFCFS; i++)
		{
			bool done=false;
			done = static_cast<FCFS*>(P_Processor[i])->KillProcess();
			if (done)
				break;
		}
		if (mode == 1 || mode == 2)
		{
			UIPtr->UpdateInterface(this, mode);
		}
		timestep++;

	}
	if(mode ==3)
		UIPtr->UpdateInterface(this, mode);
	OP_File();
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

void Scheduler::PrintProcessor(int index)
{
	P_Processor[index]->PrintReady();
}

void Scheduler::PrintBLK()
{
	BLK.Print(BLK.Getcount(), " BLK: ");
}

void Scheduler::PrintTRM()
{
	TRM.Print(TRM.Getcount(), " TRM: ");
}

int Scheduler::GetRunningID(int index)
{
	Process* p;
	p = P_Processor[index]->getRunningProcess();
	if (p)
		return p->getPID();
	else
		return -1;
}

void Scheduler::CalcLStQueue()
{
	int min=0;
	int max=0;
	Processor* lP = NULL;
	Processor* sP = NULL;
	if (PP > 0) {
		sP = lP = P_Processor[0];
		min = max = P_Processor[0]->GetTimetoFinish();

	}

	for (int i = 1;i < PP;i++)
	{
		if (P_Processor[i]->GetTimetoFinish() < min)
		{
			min = P_Processor[i]->GetTimetoFinish();
			sP = P_Processor[i];
		}
		else if (P_Processor[i]->GetTimetoFinish() > max)
		{
			max = P_Processor[i]->GetTimetoFinish();
			lP = P_Processor[i];
		}
	}
	ShortQueue = min;
	LongQueue = max;
	LP = lP;
	SP = sP;
}

void Scheduler::SearchOrphan(Process* p)
{
	bool done = false;
	for (int i = 0; i < NFCFS&&!done; i++)
		done = static_cast<FCFS*>(P_Processor[i])->OrphanPosition(p);
}

void Scheduler::BackToReady()
{
	Process* p;
	if (BLK.peek(p))
	{
		if (p->Get_TimeToReadyBack() == timestep)
		{
			CalcLStQueue();
			BLK.dequeue(p);
			SP->AddToReady(p);
			p->PopFirstIO();
			if (BLK.peek(p))
			{
				p->Set_TimeToReadyBack(timestep);
			}
		}
		
	}
}


