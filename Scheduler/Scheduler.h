#pragma once

#include"../Processor/FCFS.h"
#include"../Processor/RR.h"
#include"../Processor/SJF.h"
#include "../Processor/EDF.h"
#include"../UI/UI.h"
#include<cstdlib>
class UI;
class Scheduler
{
	Processor** P_Processor; // Array of Processors in system
	int timestep;
	ofstream outfile; // Object of Ifstream Will Read From Input File 
	ifstream Infile;  // Object of Ofstream Will Write in output file
	UI* UIPtr; ///pointer IO
	int PP;    ////numbe of processores NFCFS+NSJF+NRR+EDF
	int NFCFS; ///number of first come first serve CPU
	int NSJF;  /// number of shortest job first CPU
	int NRR;   /// number of round robin CPU
	int NEDF;  /// number of Earlist deadline first
	int NP;    ///number of processes
	int TS;    ///time slice for Round Robin 
	int RTF;   ///if the time in a process in RR less than RTF it return to scheduler and then went to SJF    RR->>>sjf
	int MAXW;  /// max time waiting   FCFS->>>>RR
	int STL;   /// every time stl will calculate  ->>> _steal limit   
	int fork;  /// forking probability
	Processor* SP;  // shortest queue in the processor
	Processor* LP;  //longest queue in the  processor
	Queue<Process*>NEW;
	Queue<Process*>BLK;
	Queue<Process*>TRM;
	Queue<Process*>StopQueue;
	Queue<Process*>StoppingForkedProcess;

	int ShortQueue;
	int LongQueue;





	float AVG_WT;
	float AVG_RT;
	float AVG_TRT;
	int StopTimeSteps;




public:
	Scheduler();
	void Load(string FileName);
	void OP_File();
	void SetNP(int n);
	void SetP_Processor();
	void AddToNEW(Process* P);
	void AddToBLK(Process* P);
	void AddToTRM(Process* P);
	void AddToStoppingForked(Process* p);
	float CalcStealLimit();
	int GetNFCFS()const;
	int GetNSJF()const;
	int GetNRR()const;
	int GetNP();
	int GetPP()const;
	int GetTS()const;
	int GetTimeStep()const;
	int GetRTF()const;
	int GetMAXW()const;
	int getForkProbabilty();
	void Simulate();
	int RunningProcessors()const;
	void PrintProcessor(int index);
	void PrintBLK();
	void PrintTRM();
	int GetRunningID(int index);
	void CalcLStQueue();
	void SearchOrphan(Process* p);
	/*this function return the process which finish IO request to the shortest queue*/
	void BackToReady();
	void KillFCFS_Process();
	void StopProcessor();
	void TurnOnProcessor();
	bool MoveToShortest(Process*& p, string type);
	void Forking();
};

#include"../Processor/Processor.h"