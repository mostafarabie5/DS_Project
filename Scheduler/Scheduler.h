#pragma once

#include"../Processor/FCFS.h"
#include"../Processor/RR.h"
#include"../Processor/SJF.h"
#include"../UI/UI.h"
#include<cstdlib>
class UI;
class Scheduler
{
	Processor** P_Processor;
	
	int timestep;
	ofstream outfile;
	ifstream Infile;


	UI* UIPtr; ///pointer IO
	int PP; ////NFCFS+NSJF+NRR
	int NFCFS; ///number of first come first serve CPU
	int NSJF;  /// number of shortest job first CPU
	int NRR;   /// number of round robin CPU
	int NP;    ///number of processes
	int TS;    ///time slice for Round Robin 
	int RTF;   ///if the time in a process in RR less than RTF it return to scheduler and then went to SJF    RR->>>sjf
	int MAXW;  // max time waiting   FCFS->>>>RR
	int STL;   // every time stl will calculate  ->>> _steal limit   
	int fork;  // forking probability


	Queue<Process*>NEW;
	Queue<Process*>BLK;
	Queue<Process*>TRM;/// must  be  changed  to  priority  queue

	int ShortQueue;
	int LongQueue;
	Processor* LP;  //longest queue in the  processor
	Processor* SP;  // shortest queue in the processor






	float AVG_WT;
	float AVG_RT;
	float AVG_TRT;




public:
	Scheduler();
	void Load(string FileName);
	void OP_File();
	void SetNFCFS(int n);
	void SetNSJF(int n);
	void SetNRR(int n);
	void SetNP(int n);
	void SetTS(int t);
	void SetP_Processor();
	void AddToNEW(Process* P);
	void AddToBLK(Process* P);
	void AddToTRM(Process* P);
	void SetPP(int n);
	float CalcStealLimit();

	void PassProcessTo(Process* P);   ////  will use in stl  to pop from longest  ready qeueu of one processors to shortest one 
	void CreatNewPro(int T, int ct); ///take  AT= time step  the remaining CT is the new pro CT
	int GetNFCFS()const;
	int GetNSJF()const;
	int GetNRR()const;
	int GetTS()const;
	int GetTimeStep()const;
	void Simulate();

	int RunningProcessors()const;
	void PrintProcessor(int index);
	void PrintBLK();
	void PrintTRM();
	int GetRunningID(int index);


	void CalcLStQueue();
	

};

#include"../Processor/Processor.h"