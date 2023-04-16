#pragma once
#include"../Scheduler/Scheduler.h"
class Scheduler;
class UI
{

public:
	UI();
	void UpdateInterface(Scheduler* SchedPtr,int count);
	int ReadMode();
	string ReadFileName();
};

