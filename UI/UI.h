#pragma once
#include"../Scheduler/Scheduler.h"
class Scheduler;
class UI
{


public:
	/*Default constructor */
	UI();
	/*function which is responsible to output the data in console depending on the Mode*/
	void UpdateInterface(Scheduler* SchedPtr, int mode)const;
	/*read the mode  type from user */
	int ReadMode()const;
	/*read the input file name from user*/
	string ReadFileName()const;
};

