#pragma once

#include"../Processor/FCFS.h"
#include"../Processor/RR.h"
#include"../Processor/SJF.h"
#include"../UI/UI.h"
class UI;
class Scheduler
{
	Processor** PTR_FCFS;
	Processor** PTR_SJF;
	Processor** PTR_RR;


	ofstream outfile;
	ifstream Infile;


	UI* UIPtr; ///pointer IO

	int NFCFS; ///number of first come first serve CPU
	int NSJF;  /// number of shortest job first CPU
	int NRR;   /// number of round robin CPU
	int NP;    ///number of processes
	int TS;    ///time slice for Round Robin 
	int RTF;   ///if the time in a process in RR less than RTF it return to scheduler and then went to SJF    RR->>>sjf
	int MAXW;  // max time waiting   FCFS->>>>RR
	int STL;   // every time stl will calculate  ->>> _steal limit   
	int fork;  // forking probability

	Queue<Pair>SIGKILL;

	Queue<Process*>NEW;
	Queue<Process*>BLK;
	Queue<Process*>TRM;/// must  be  changed  to  priority  queue

	int ShortQueue;
	int LongQueue;
	Processor* LP;  //longest queue in the  processor
	Processor* SP;  // shortest queue in the processor


public:
	Scheduler();
	void Load(string FileName);
	//void save();
	void SetNFCFS(int n);
	void SetNSJF(int n);
	void SetNRR(int n);
	void SetNP(int n);
	void SetTS(int t);

	void AddToNEW(Process* P);
	void AddToBLK(Process* P);
	void AddToTRM(Process* P);


	int ShorestQueue();
	int LongestQueue();
	void CalcStealLimit();

	void PassProcessTo(Process* P);   ////  will use in stl  to pop from longest  ready qeueu of one processors to shortest one 
	void CreatNewPro(int T, int ct); ///take  AT= time step  the remaining CT is the new pro CT
	void Print();
	int GetNFCFS()const;
	int GetNSJF()const;
	int GetNRR()const;
	void Simulate();

	int RunningProcessors()const;

	void PrintProcessor();
	void PrintBLK();
	void PrintTRM();
	void PrintRUN();


	//bool EndProgram();

};

#include"../Processor/Processor.h"