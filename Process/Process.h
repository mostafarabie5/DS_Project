#pragma once
#include"../DS/Queue.h"
#include"../DEFS.h"
#include"fstream"
#include<iostream>
class Process
{
	int PID; // unique id for each process 
	int AT;  // Arrival time ->tack it frome input file 
	int RT;  // AT-time that p get the CPU first time 
	int CT;  // time needed to run p 
	int TT;  // time when the p finish excution
	int TRT; // the total time   TT-AT
	int WT;  // TRT-CT
	Queue<Pair*> IO;   //First is IO_R ---------- Second is IO_D
	int NUM_IO;    // number of IO operation 
	int RemainingTime;  // the time to finish executing and go to terminated list
	int TransitionTime;		// Last transition time of the process.
	Process* child;  // pointer to its child when forking
	int Total_IO_D;
public:
	Process();
	Process(int AT, int PID, int CT);
	void SetAT(int at);
	void SetCT(int ct);
	void SetPID(int id);
	void SetNUM_IO(int n);

	void setPair(int first, int second);
	void SetTransition(int t) { TransitionTime = t; }
	void DecreaseRemainingTime();
	void SetTT(int x);
	void SetTRT();
	void SetWT();
	void PrintID();
	int getAT();
	int getCT();
	int getPID();
	int getTT();
	int getTRT();
	int get_Total_IO_D();
	int getWT();
	int getRT();
	int getTransition() { return TransitionTime; }
	int getRemainingTime();
	void setRT(int x);
	~Process();
	bool blk_request(int timestep);
	friend bool operator >(Process p1, Process p2);
	friend bool operator !=(Process p1, Process P2);
	friend std::ostream& operator <<(std::ostream& out, Process* p);
};

