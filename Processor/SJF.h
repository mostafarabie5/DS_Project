#pragma once
#include "Processor.h"
class SJF :public Processor
{
    PriorityQueue<Process*> ReadyList;
public:
    SJF(Scheduler* sched_ptr, int num);
    /*function that run the process depending on type of the processor*/
    void SchedulerAlgo();
    /*Move process from New Queue to Raedy Queue */
    void AddToReady(Process* P);
    /*printing Ready Queue in console*/
    void PrintReady()const;
    /*return number of items in ready list*/
    int NumRDY()const;
    /*Move the process from ready to run */
    Process* Delete_FirstProcess();
    /*Check if ready is empty return true else retrun false */
    bool Ready_isEmpty()const;
    /*Move the process from ready to run */
    void AddToRun();
    ~SJF();
};