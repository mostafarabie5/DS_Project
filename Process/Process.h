#pragma once
#include"../DS/Pair.h"
#include"../DS/Queue.h"
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
	Queue <Pair> IO;  //(IO_R,IO_D)   / ...Array of pair 
	int NUM_IO;    // number of IO operation 
	int RemainingTime;  // the time to finish executing and go to terminated list

	Process* child;  // pointer to its child when forking


public:
	Process();
	Process(int AT, int PID, int CT, Queue<Pair> IO_Time);
	void SetAT(int at);
	void SetCT(int ct);
	void SetPID(int id);
	void SetNUM_IO(int n);
	void setPair(int first, int second);
	void DecreaseRemainingTime();
	void PrintID();
	int getAT();
	int getCT();
	int getPID();
	int getRemainingTime();
	~Process();
	friend bool operator>(Process p1, Process p2);
	friend bool operator !=(Process p1, Process P2);
	friend std::ostream& operator <<(std::ostream& out, Process* p);
};

