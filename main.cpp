#include"Process.h"
#include"Processor/FCFS.h"
#include"Processor/RR.h"
#include"Processor/SJF.h"
#include<iostream>
using namespace std;

int main()
{
	srand(time(0));
	Scheduler master;
	master.Simulate();

	return 0;
}