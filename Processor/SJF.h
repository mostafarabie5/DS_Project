#pragma once
#include "Processor.h"
class SJF :public Processor
{
    PriorityQueue<Process*> ReadyList;
public:
    SJF(Scheduler* sched_ptr,int num);
    void SchedulerAlgo();
    void AddToReady(Process* P);
    void PrintReady();
    int NumRDY()const; // return number of items in ready list
    int CalcTimeToFinish();
    void AddToRun();
    void Run();
};

