#pragma once
#include"../DS/Queue.h"
#include"../DEFS.h"
#include"fstream"
#include<iostream>
class Process
{
	bool Steal;           // bool true if the process has been stolen
	bool Migrate_RR_SJF;  // bool true if the process is migrated from RR->>SJF
	bool Migrate_FCFS_RR; // bool true if the process is migrated from FCFS->>RR
	bool IsForked;        // bool true if the process has benn forked 
	bool IsKilled;        // bool true if the process killed
	int PID;              // unique id for each process 
	int AT;               // Arrival time ->tack it frome input file 
	int RT;               // time that p get the CPU first time 
	int CT;               // time needed to run p 
	int TT;               // time when the p finish excution
	int TRT;              // the total time   TT-AT
	int WT;               // the total waiting time TRT-CT
	Queue<Pair*> IO;      //First is IO_R ---------- Second is IO_D
	int NUM_IO;           // number of IO request
	int RemainingTime;    // the time to finish executing and go to terminated list
	Process* LChild;      // pointer to its left child when forking
	Process* RChild;      // pointer to its right child when forking
	Process* Parent;      // pointer to parent process 
	bool IsChild;         // true if the process is a chiled to another one 
	int Total_IO_D;       // total duration of io 
	int TimeToReadyBack;  //the time at which the process return to ready queue 
	int DeadLine;         // time needed to be finished excution before 
public:
	/*defult constructor*/
	Process();
	/*parameterized constructor*/
	Process(int at, int pid, int ct, int num_io = 0, int deadline = 0);
	/*Set if that process a child to another one */
	void SetIsChild();
	/*setter for the left child */
	void SetLChild(Process* P);
	/*Setter for the right child*/
	void SetRChild(Process* P);
	/*Set Parent of that process if exist*/
	void SetParent(Process* P);
	/*Setter for io request and duration*/
	void setPair(int first, int second);
	/*set total duration time , total trmination and waiting time*/
	void SetTT(int x);
	/*Set the first time the process get to run in a processor */
	void setRT(int x);
	/**used in moving the process from BLK to Ready Queue
	@param the timestep at the process will become the first element in the BLK queue*/
	void Set_TimeToReadyBack(int n);
	/*setter for forking */
	void SetIsForked(bool n);
	/*setter for steal*/
	void Setsteal(bool n);
	/*setter for killing*/
	void SetIsKilled(bool n);
	/*setter for migration */
	void SetMigrate_RR_SJF(bool n);
	/*setter for migration */
	void SetMigrate_FCFS_RR(bool n);
	/*Return Arrival time */
	int getAT()const;
	/*Retrun CPU time */
	int getCT()const;
	/*return ID of the Process*/
	int getPID()const;
	/*return time of finishinng*/
	int getTT()const;
	/*return total tirmination time */
	int getTRT()const;
	/*return total duration time of IO */
	int get_Total_IO_D()const;
	/*return Waiting time  */
	int getWT()const;
	/*Return Response time */
	int getRT()const;
	/*return Remaining time of CPU*/
	int getRemainingTime()const;
	/*return Deadline time */
	int getdeadline()const;
	/*Check if that Process is a child or not */
	bool getIsChild()const;
	/*Return the pointer to th Right  child process (Forked Process)*/
	Process* getRChild()const;
	/*Return Pointer to the Left Child process (Forked Process)*/
	Process* getLChild()const;
	/*Return ID of the Parent Process*/
	int getParentID()const;
	/*return the timestep when the process will move from BLK queue to Shortest ready list*/
	int Get_TimeToReadyBack()const;
	/*check whether that process is stolen and
	return true otherwise return false  */
	bool Getsteal()const;
	/*check whether that process has been forked and
	return true otherwise return false  */
	bool GetIsForked()const;
	/*check whether that process has been migrated from FCFS Processor to RR processor and
	return true otherwise return false  */
	bool GetMigrate_FCFS_RR()const;
	/*check whether that process has been migrated from the RR processor to SJF processor and
	return true otherwise return false  */
	bool GetMigrate_RR_SJF()const;
	/*check whether that process has been killed and
	return true otherwise return false  */
	bool GetIsKilled()const;
	/*return true if the process request IO at that time */
	bool blk_request(int timestep)const;
	/*delete the first IO pair after the process return to ready queue*/
	void PopFirstIO();
	/*Decreasing the time Remaining of CPU time*/
	void DecreaseRemainingTime();
	bool operator >(Process p2);
	bool operator <(Process p2);
	bool operator !=(Process P2);
	friend std::ostream& operator <<(std::ostream& out, Process* p);
	~Process();
};

