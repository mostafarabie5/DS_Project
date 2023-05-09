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
	Process* child;  // pointer to its child when forking
	int Total_IO_D;
	int TimeToReadyBack;  //the time at which the process return to ready queue 
public:
	Process();
	Process(int AT, int PID, int CT);
	void SetAT(int at);
	void SetCT(int ct);
	void SetPID(int id);
	void SetNUM_IO(int n);

	void setPair(int first, int second);
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
	int getRemainingTime();
	void setRT(int x);
	~Process();
	bool blk_request(int timestep);
	/**used in moving the process from BLK to Ready Queue
	@param the timestep at the process will become the first element in the BLK queue*/
	void Set_TimeToReadyBack(int n);
	/*return the timestep when the process will move from BLK queue to Shortest ready list*/
	int Get_TimeToReadyBack();
	/*Return the pointer the child process (Forked Process)*/
	Process* GetChild();
	/*delete the first IO pair after the process return to ready queue*/
	void PopFirstIO();

	friend bool operator >(Process p1, Process p2);
	friend bool operator !=(Process p1, Process P2);
	friend std::ostream& operator <<(std::ostream& out, Process* p);
};

