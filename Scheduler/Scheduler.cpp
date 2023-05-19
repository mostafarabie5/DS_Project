#include "Scheduler.h"
#include<iostream>
//---------------------------------------- (Default constructor) -----------------------------------------------------------------//
Scheduler::Scheduler()
{
	P_Processor = nullptr;
	AVG_RT = AVG_TRT = AVG_WT = 0;
	timestep = 1;
	LP = SP = nullptr;
	StopTimeSteps = 2;
	OverHeat = 4;
	PP = NFCFS = NSJF = NRR = NEDF = NP = TS = RTF = MAXW = STL = fork = 0;
	UIPtr = new UI;
}
//-----------------------------------------(Setter functions)----------------------------------------------------------------//
void Scheduler::SetNP(int n)
{
	NP = n;
}

void Scheduler::SetP_Processor()
{
	int n = NFCFS + NSJF + NRR + NEDF;
	PP = n;
	P_Processor = new Processor * [n];
	int i = 0;
	for (; i < NFCFS; i++)
	{
		P_Processor[i] = new FCFS(this, i + 1);
	}
	for (; i < NFCFS + NSJF; i++)
	{
		P_Processor[i] = new SJF(this, i + 1);
	}
	for (; i < NFCFS + NSJF + NRR; i++)
	{
		P_Processor[i] = new RR(this, i + 1);
	}
	for (; i < n; i++)
	{
		P_Processor[i] = new EDF(this, i + 1);
	}
}

//------------------------------------------(Getters Functions)---------------------------------------------------------------//
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

int Scheduler::GetNP() const
{
	return NP;
}

int Scheduler::GetPP() const
{
	return PP;
}

int Scheduler::GetTS() const
{
	return TS;
}

int Scheduler::GetTimeStep() const
{
	return timestep;
}

int Scheduler::GetRTF() const
{
	return RTF;
}

int Scheduler::GetMAXW() const
{
	return MAXW;
}

int Scheduler::getForkProbabilty() const
{
	return fork;
}

int Scheduler::getTotalTRT() const
{
	return AVG_TRT * NP;
}

//-----------------------------------------------(Adding data to Diffrente Queues )----------------------------------------------------------//
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
	AVG_RT = AVG_RT + P->getRT() / float(NP);
	AVG_TRT = AVG_TRT + P->getTRT() / float(NP);
	AVG_WT = AVG_WT + P->getWT() / float(NP);
	TRM.enqueue(P);
}
//-----------------------------------------------(loading the input data from the file )----------------------------------------------------------//

void Scheduler::Load(string FileName)
{
	Infile.open(FileName + ".txt", ios::in);
	Infile >> NFCFS >> NSJF >> NRR >> NEDF;
	SetP_Processor();
	Infile >> TS >> StopTimeSteps;
	Infile >> RTF >> MAXW >> STL >> fork;
	Infile >> NP;
	for (int i = 0; i < NP; i++)
	{
		int AT, PID, CT, NUM_IO, deadline;
		Infile >> AT >> PID >> CT >> deadline>>NUM_IO ;
		Process* ptr = new Process(AT, PID, CT, NUM_IO,deadline);
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
//-------------------------------------------(printing data in output file )--------------------------------------------------------------//

void Scheduler::OP_File()
{
	outfile.open("OutputFile.txt", ios::out);
	outfile << "TT        PID       AT        CT        IO_D      WT        RT        TRT       Deadline" << endl;
	Process* p;
	float num_p = 0;
	float num_steal_p = 0;
	float num_Killed_p = 0;
	float num_forked_p = 0;
	float num_M_RR_SJF = 0;
	float num_M_FCFS_RR = 0;

	for (int i = 0; i < NP; i++)
	{
		TRM.dequeue(p);
		outfile << left << setw(10) << p->getTT() << setw(10) << p->getPID() << setw(10) << p->getAT() << setw(10) << p->getCT() << setw(10) << p->get_Total_IO_D();
		outfile << setw(10) << p->getWT() << setw(10) << p->getRT() << setw(10) << p->getTRT() << setw(10) << p->getdeadline();
		outfile << endl;
		if (p->getTT() < p->getdeadline())
			num_p++;
		if (p->Getsteal())
			num_steal_p++;
		if (p->GetIsKilled())
			num_Killed_p++;
		if (p->GetIsForked())
			num_forked_p++;
		if (p->GetMigrate_RR_SJF())
			num_M_RR_SJF++;
		if (p->GetMigrate_FCFS_RR())
			num_M_FCFS_RR++;
		delete p;
		p = NULL;
	}

	outfile << endl << "Processes : " << NP << endl;
	outfile << "AVG WT=" << setw(7) << AVG_WT << "      " << "AVG RT=" << setw(7) << AVG_RT << "      " << "AVG TRT=" << setw(7) << AVG_TRT << endl;
	outfile << setw(19) << "Migiration :%" << "RTF = " << (num_M_RR_SJF / NP) * 100 << " %" << "        " << "MaxW = " << (num_M_FCFS_RR / NP) * 100 << " %" << endl;
	outfile << setw(19) << "Work Steal :" << setw(7) << (num_steal_p / NP) * 100 << " %" << endl;
	outfile << setw(19) << "Forked Processes :" << setw(7) << (num_forked_p / NP) * 100 << " %" << endl;
	outfile << setw(19) << "killed Proceeses :" << setw(7) << (num_Killed_p / NP) * 100 << " %" << endl << endl;
	outfile << endl << "Processors : " << PP << " [" << NFCFS << " FCFS ," << NSJF << " SJF ," << NRR << " RR , " << NEDF << " DEF ]" << endl;
	outfile << "Procesores load" << endl;
	for (int i = 0; i < PP; i++)
	{
		outfile << "P" << i + 1 << " = " << setw(7) << P_Processor[i]->CalcPLoad() << " %";
		outfile << "    ";
	}
	outfile << endl << endl;
	outfile << "Processores Utiliz" << endl;
	float sum = 0;
	for (int i = 0; i < PP; i++)
	{
		sum += P_Processor[i]->CalcPUtil();
		outfile << "P" << i + 1 << " = " << setw(7) << P_Processor[i]->CalcPUtil() << " %";
		outfile << "    ";
	}
	outfile << endl;
	outfile << "AVG Utilization = " << sum / PP << " %";
	outfile << endl << endl;
	outfile << "Percentage of Process completed before expected deadline = ";
	outfile << (num_p / NP) * 100 << " %";
}
//------------------------------------------(Function which calculate the Steal Limit)---------------------------------------------------------------//

float Scheduler::CalcStealLimit() const
{
	float StealLimit;
	if (LP)
		if (LP->NumRDY() > 0)
		{
			StealLimit = ((float(LP->GetTimetoFinish()) - SP->GetTimetoFinish()) / LP->GetTimetoFinish()) * 100;
			return StealLimit;
		}
	return 0;
}

//---------------------------------------------(Simulation function)------------------------------------------------------------//

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
		TurnOnProcessor();
		StopProcessor();

		if (NEW.peek(P))
		{
			while (NEW.peek(P) && P->getAT() == timestep)
			{
				MoveToShortest("ALL");
				NEW.dequeue(P);
				if (SP)
					SP->AddToReady(P);
				else
					StopQueue.enqueue(P);
			}
		}

		for (int i = 0; i < PP; i++)
		{
			P_Processor[i]->SchedulerAlgo();
		}

		BackToReady();

		if (timestep % STL == 0)
		{
			MoveToShortest("ALL");
			while (CalcStealLimit() > 40)
			{
				Process* P = LP->Delete_FirstProcess();

				if (P)
				{
					P->Setsteal(true);
					SP->AddToReady(P);
				}
				else
					break;
			}
		}
		Forking();
		KillFCFS_Process();

		if (mode == 1 || mode == 2)
		{
			UIPtr->UpdateInterface(this, mode);
		}
		timestep++;

	}
	if (mode == 3)
		UIPtr->UpdateInterface(this, mode);
	OP_File();
}

//---------------------------------------------(Return Number of Busy Processores )------------------------------------------------------------//

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
//--------------------------------------------(Functions for Handiling the program Interface)-------------------------------------------------------------//

void Scheduler::PrintProcessor(int index) const
{
	P_Processor[index]->PrintReady();
}

void Scheduler::PrintBLK() const
{
	BLK.Print(BLK.Getcount(), " BLK: ");
}

void Scheduler::PrintTRM() const
{
	TRM.Print(TRM.Getcount(), " TRM: ");
}
//-----------------------------------------(funtion return the ID of the running process in a processor which have the passed index)---------------------------------//

int Scheduler::GetRunningID(int index) const
{
	Process* p;
	p = P_Processor[index]->getRunningProcess();
	if (p)
		return p->getPID();
	else
		return -1;
}

//----------------------------------------------------(search for an orphen in the FCFS processors)-----------------------------------------------------//

void Scheduler::SearchOrphan(Process* p) const
{
	bool done = false;
	for (int i = 0; i < NFCFS && !done; i++)
		done = static_cast<FCFS*>(P_Processor[i])->OrphanPosition(p);
}
//-----------------------------------------------(move process from the BLK Queue to the Shortest ready Queue )-----------------------------------------------------------//

void Scheduler::BackToReady()
{
	Process* p;

	if (BLK.peek(p))
	{
		if (p->Get_TimeToReadyBack() == timestep)
		{
			MoveToShortest("ALL",p);
			BLK.dequeue(p);
			p->PopFirstIO();
			if (BLK.peek(p))
			{
				p->Set_TimeToReadyBack(timestep);
			}
		}

	}
}
//-----------------------------------------------(Killing the Process which is in FCFS Processor)----------------------------------------------------------//

void Scheduler::KillFCFS_Process()
{
	for (int i = 0; i < NFCFS; i++)
	{
		bool done = false;
		done = static_cast<FCFS*>(P_Processor[i])->KillProcess();
		if (done)
			break;
	}
}

//------------------------------------------(Stopping Processors that are Overheat)---------------------------------------------------------------//

void Scheduler::StopProcessor()
{
	for (int i = 0; i < PP; i++)
	{
		int num = rand() % 100;
		if (num < OverHeat && !P_Processor[i]->get_StopMode())
		{
			Process* temp;
			P_Processor[i]->set_StopMode(true);
			P_Processor[i]->set_ActiveAtTime(StopTimeSteps + timestep);
			MoveToShortest("ALL");
			temp = P_Processor[i]->getRunningProcess();
			P_Processor[i]->SetRunningProcess(nullptr);
			if (temp)
			{
				if (temp->getIsChild())
				{
					if (!MoveToShortest("FCFS", temp))
						StoppingForkedProcess.enqueue(temp);
				}
				else
					MoveToShortest("ALL", temp);
			}
			while (!P_Processor[i]->Ready_isEmpty())
			{
				MoveToShortest("ALL");
				if (i < NFCFS)
				{
					temp = static_cast<FCFS*>(P_Processor[i])->removeProcess();
				}
				else
					temp = P_Processor[i]->Delete_FirstProcess();
				if (temp->getIsChild())
				{
					if (!MoveToShortest("FCFS", temp))
						StoppingForkedProcess.enqueue(temp);
				}
				else
					MoveToShortest("ALL", temp);
			}

		}
	}
}
//---------------------------------------------(Return the processors to work)------------------------------------------------------------//

void Scheduler::TurnOnProcessor()
{
	for (int i = 0; i < PP; i++)
	{
		if (P_Processor[i]->get_StopMode() && P_Processor[i]->get_ActiveAtTime() == timestep)
		{
			P_Processor[i]->set_StopMode(false);
			P_Processor[i]->set_ActiveAtTime(0);
		}
	}
	while (!StoppingForkedProcess.isEmpty())
	{
		Process* p;
		StoppingForkedProcess.peek(p);
		if (MoveToShortest("FCFS", p))
		{
			StoppingForkedProcess.dequeue(p);
		}
		else
			break;
	}
	while (!StopQueue.isEmpty())
	{
		MoveToShortest("ALL");
		if (!SP)
			break;
		Process* p;
		StopQueue.dequeue(p);
		SP->AddToReady(p);
	}
}
//-----------------------------------------------(Moving Process to the Shortest ready Queue)----------------------------------------------------------//

bool Scheduler::MoveToShortest(string type, Process* p)
{
	int min;
	int max;
	int index;
	min = -1;
	max = -1;
	int num_p;
	if (type == "ALL")
	{
		num_p = PP;
		index = 0;
	}
	else if (type == "FCFS")
	{
		num_p = NFCFS;
		index = 0;
	}
	else if (type == "SJF")
	{
		num_p = NFCFS + NSJF;
		index = NFCFS;
	}
	else
	{
		num_p = NFCFS + NSJF + NRR;
		index = NFCFS + NSJF;
	}


	while (index < num_p)
	{
		if (!P_Processor[index]->get_StopMode())
		{
			min = max = index;
			break;
		}
		index++;
	}
	if (min == -1 && num_p == PP)
	{
		LP = NULL;
		SP = NULL;
		if (p)
		{
			if (p->getIsChild())
				StoppingForkedProcess.enqueue(p);
			else
				StopQueue.enqueue(p);
		}
	}
	else if (min == -1)
	{
		return false;
	}
	else
	{
		int i = min + 1;
		while (i < num_p)
		{
			if (!P_Processor[i]->get_StopMode() && P_Processor[min]->GetTimetoFinish() > P_Processor[i]->GetTimetoFinish())
			{
				min = i;
			}
			if (!P_Processor[i]->get_StopMode() && P_Processor[max]->GetTimetoFinish() < P_Processor[i]->GetTimetoFinish())
			{
				max = i;
			}
			i++;
		}
		LP = P_Processor[max];
		SP = P_Processor[min];
		if (p)
		{
			P_Processor[min]->AddToReady(p);
		}
	}
	return true;
}
//---------------------------------------------------------------------------------------------------------//

void Scheduler::Forking()
{
	for (int i = 0; i < NFCFS; i++)
	{
		if (!P_Processor[i]->get_StopMode())
			static_cast<FCFS*>(P_Processor[i])->AddForkedProcess();
	}
}

Scheduler::~Scheduler()
{
	for (int i = 0; i < PP; i++)
	{
		delete  P_Processor[i];
	}
	delete[] P_Processor;
	delete  UIPtr;
}