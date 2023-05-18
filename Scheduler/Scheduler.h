#pragma once

#include"../Processor/FCFS.h"
#include"../Processor/RR.h"
#include"../Processor/SJF.h"
#include "../Processor/EDF.h"
#include"../UI/UI.h"
#include<cstdlib>
#include<iomanip>
class UI;
class Scheduler
{
	Processor** P_Processor;  // Array of Processors in system
	int timestep;             //
	ofstream outfile;         // Object of Ifstream Will Read From Input File 
	ifstream Infile;          // Object of Ofstream Will Write in output file
	UI* UIPtr;                //pointer IO
	int PP;                   //numbe of processores NFCFS+NSJF+NRR+EDF
	int NFCFS;                //number of first come first serve CPU
	int NSJF;                 // number of shortest job first CPU
	int NRR;                  // number of round robin CPU
	int NEDF;                 // number of Earlist deadline first
	int NP;                   //number of processes
	int TS;                   //time slice for Round Robin 
	int RTF;                  //if the time in a process in RR less than RTF it return to scheduler and then went to SJF    RR->>>sjf
	int MAXW;                 // max time waiting   FCFS->>>>RR
	int STL;                  // every time stl will calculate  ->>> _steal limit   
	int fork;                 // forking probability
	Processor* SP;            // shortest queue in the processor
	Processor* LP;            //longest queue in the  processor
	Queue<Process*>NEW;       //New queue have the process which has came at that time step
	Queue<Process*>BLK;       // IO quque has the process which needs io
	Queue<Process*>TRM;       // Queue has the processes that finished the needed CPU time 
	Queue<Process*>StopQueue; //
	Queue<Process*>StoppingForkedProcess;//
	float AVG_WT;             // Average wating time of all the processes
	float AVG_RT;             // Average rsponse time of all the processes
	float AVG_TRT;            // Average total tirmination time  of all the processes
	int StopTimeSteps;        // 
	int OverHeat;             //


public:
	/*Copy construcror */
	Scheduler();
	/*setter for Number of process*/
	void SetNP(int n);
	/*Setter for Number of  Processors*/
	void SetP_Processor();
	/*function get the data from file and set this data */
	void Load(string FileName);
	/*Create the output file that has the needed data*/
	void OP_File();
	/*Moving  process to new Queue*/
	void AddToNEW(Process* P);
	/*Moving process that needs Io to BLK Queue*/
	void AddToBLK(Process* P);
	/*Moving Process that finishes CPU time to Tirmination Queue*/
	void AddToTRM(Process* P);
	/*function that return the steal limit between the longest and shortest queue*/
	float CalcStealLimit()const;
	/*Get  Number of FCFC Processors*/
	int GetNFCFS()const;
	/*Get Number of SJF Processors*/
	int GetNSJF()const;
	/*Get Number of NRR Processors*/
	int GetNRR()const;
	/*Get Number of the Processes*/
	int GetNP()const;
	/*Get Number of the Processors*/
	int GetPP()const;
	/*Get time slice  */
	int GetTS()const;
	/*Getter for Timestep */
	int GetTimeStep()const;
	/*Gette for RTF time*/
	int GetRTF()const;
	/*Getter for Max time waiting */
	int GetMAXW()const;
	/*Getter for the probability of the process to be forked*/
	int getForkProbabilty()const;
	/*Get total tirmination time of all prcesses*/
	int getTotalTRT()const;
	/*function that has to run all the system */
	void Simulate();
	/*Return Number of Busy Processores*/
	int RunningProcessors()const;
	/*printing the exist processors and its ready queue in console*/
	void PrintProcessor(int index)const;
	/*Print processes in the BLK queue in console */
	void PrintBLK()const;
	/*Print processes in the TRM queue in console */
	void PrintTRM()const;
	/*funtion return the ID of the running process in a processor which have the passed index*/
	int GetRunningID(int index)const;
	/*search for orphen in the FCFS Processors*/
	void SearchOrphan(Process* p)const;
	/*this function return the process which finish IO request to the shortest queue*/
	void BackToReady();
	/*move the Killed Processes to TRM queue*/
	void KillFCFS_Process();
	/*stop overheat processor from working move all the processes in ready and run to the Shortest Queue */
	void StopProcessor();
	/*return the Processor to the work*/
	void TurnOnProcessor();
	/*function that move the process to the Shortest queue*/
	bool MoveToShortest(string type, Process* p = NULL);
	/**/
	void Forking();
};

#include"../Processor/Processor.h"