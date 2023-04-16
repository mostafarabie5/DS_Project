#include"Process.h"
#include"Processor/FCFS.h"
#include"Processor/RR.h"
#include"Processor/SJF.h"
#include<iostream>
using namespace std;

int main()
{
	Scheduler* s = new Scheduler;
	s->SetNFCFS(2);
	s->SetNRR(1);
	s->SetNSJF(1);
	s->Simulate();


}