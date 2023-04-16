#include "Scheduler.h"
Scheduler::Scheduler()
{

}

void Scheduler::Load(string FileName)
{
	//Infile.open("text");
	//int n_f, n_s, n_r;
	//Infile >> n_f >> n_s >> n_r;
	//SetNFCFS(n_f);
	//SetNSJF(n_s);
	//SetNRR(n_r);


	//Infile >> TS;
	//Infile >> RTF >> MAXW >> STL >> fork;
	//Infile >> NP;
	//for (int i = 0; i < NP; i++)
	//{
	//	int AT, PID, CT, NUM_IO;
	//	Pair IO;
	//	Queue<Pair>IO_Time;
	//	Infile >> AT >> PID >> CT >> NUM_IO;
	//	for (int i = 0; i < NUM_IO; i++)
	//	{
	//		//Infile >> IO.First;
	//		while (1)
	//		{
	//			if (Infile.fail())
	//			{
	//				Infile.clear();
	//				Infile.ignore(numeric_limits<streamsize>::max(), '\n');
	//				Infile >> IO.First;
	//			}
	//			if (!cin.fail())
	//				break;
	//		}
	//		Infile >> IO.Second;
	//		while (1)
	//		{
	//			if (Infile.fail())
	//			{
	//				Infile.clear();
	//				Infile.ignore(numeric_limits<streamsize>::max(), '\n');
	//				Infile >> IO.Second;
	//			}
	//			if (!cin.fail())
	//				break;
	//		}

	//		IO_Time.enqueue(IO);
	//	}

	//	Process* p = new Process(AT, PID, CT, IO_Time);
	//	AddToNEW(p);
	//}
	//while (!Infile.eof())
	//{
	//	Pair s;
	//	Infile >> s.First >> s.Second;
	//	SIGKILL.enqueue(s);
	//}

}

void Scheduler::SetNFCFS(int n)
{
	NFCFS = n;
	PTR_FCFS = new Processor * [n];
	for (int i = 0; i < NFCFS; i++)
	{
		PTR_FCFS[i] = new FCFS( i + 1);
	}
}

void Scheduler::SetNSJF(int n)
{
	NSJF = n;
	PTR_SJF = new Processor * [n];
	for (int i = 0; i < NSJF; i++)
	{
		PTR_SJF[i] = new SJF( i + 1 + NFCFS);
	}
}

void Scheduler::SetNRR(int n)
{
	NRR = n;
	PTR_RR = new Processor * [n];
	for (int i = 0; i < NRR; i++)
	{
		PTR_RR[i] = new RR( (i + 1 + NFCFS + NSJF));
	}
}

void Scheduler::SetNP(int n)
{
	NP = n;
}


void Scheduler::SetTS(int t)
{
	TS = t;
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

void Scheduler::Simulate()
{

	Queue<Pair> q;
	Process* pp = new Process(5, 1, 22, q);
	PTR_FCFS = new Processor * [2];
	PTR_FCFS[0] = new FCFS(1);
	PTR_FCFS[1] = new FCFS(5);
	PTR_SJF = new Processor * [1];
	PTR_SJF[0] = new SJF(2);
	PTR_RR = new Processor * [1];
	PTR_RR[0] = new RR(3);
	PTR_FCFS[0]->AddToReady(pp);
	pp = new Process(7, 2, 20, q);
	PTR_SJF[0]->AddToReady(pp);
	pp = new Process(13, 3, 30, q);
	PTR_RR[0]->AddToReady(pp);
	pp = new Process(20, 10, 44, q);
	PTR_FCFS[1]->AddToReady(pp);
	pp = new Process(25, 11, 44, q);
	PTR_RR[0]->AddToReady(pp);
	pp = new Process(26, 13, 44, q);
	PTR_RR[0]->AddToReady(pp);
	pp = new Process(28, 14, 10, q);
	PTR_SJF[0]->AddToReady(pp);
	pp = new Process(36, 15, 5, q);
	PTR_SJF[0]->AddToReady(pp);
	pp = new Process(46, 17, 60, q);
	PTR_SJF[0]->AddToReady(pp);



	UIPtr->UpdateInterface(this,5);
	UIPtr->UpdateInterface(this, 6);
	UIPtr->UpdateInterface(this, 7);


	//string FileName = UIPtr->ReadFileName();

	/*int n = UIPtr->ReadMode();
	Load(FileName);*/

	// check the mode 
	//// check new  
	/// check ready of the ideal processor 
	/// print 
	///
	///  call Scheduler of each process




	//End = (NP == TRM.Getcount()) ? true : false;

}

int Scheduler::RunningProcessors() const
{
	int count = 0;
	for (int i = 0; i < NFCFS; i++)
	{
		if (PTR_FCFS[i]->ProcessorState())
			count++;
	}
	for (int i = 0; i < NSJF; i++)
	{
		if (PTR_SJF[i]->ProcessorState())
			count++;
	}
	for (int i = 0; i < NRR; i++)
	{
		if (PTR_RR[i]->ProcessorState())
			count++;
	}
	return count;
}

void Scheduler::PrintProcessor()
{
	for (int i = 0; i < NFCFS; i++)
	{
		PTR_FCFS[i]->PrintReady();
	}
	for (int i = 0; i < NSJF; i++)
	{
		PTR_SJF[i]->PrintReady();
	}
	for (int i = 0; i < NRR; i++)
	{
		PTR_RR[i]->PrintReady();
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
	for (int i = 0; i < NFCFS; i++)
	{
		if (PTR_FCFS[i]->ProcessorState())
			PTR_FCFS[i]->PrintRunningProcess();
	}
	for (int i = 0; i < NSJF; i++)
	{
		if (PTR_SJF[i]->ProcessorState())
			PTR_SJF[i]->PrintRunningProcess();
	}
	for (int i = 0; i < NRR; i++)
	{
		if (PTR_FCFS[i]->ProcessorState())
			PTR_FCFS[i]->PrintRunningProcess();
	}
}