#include"Process.h"
#include"Processor/FCFS.h"
#include"Processor/RR.h"
#include"Processor/SJF.h"
#include<iostream>
using namespace std;

int main()
{
	/*Scheduler* s = new Scheduler;
	s->SetNFCFS(2);
	s->SetNRR(1);
	s->SetNSJF(1);
	s->Simulate();*/
	Scheduler master;
	master.SetNFCFS(2);
	master.SetNSJF(1);
	master.SetNRR(1);
	master.Simulate();

	return 0;
}