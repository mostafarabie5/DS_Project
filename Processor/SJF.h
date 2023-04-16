#pragma once
#include "Processor.h"
class SJF :public Processor
{
    PriorityQueue<Process*> ReadyList;
public:
    SJF( int num);
    void SchedulerAlgo();
    void AddToReady(Process* P);
    void PrintReady();
    int NumRDY()const; // return number of items in ready list
    int CalcTimeToFinish();

};

