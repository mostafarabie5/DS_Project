#include "UI.h"
#include "windows.h"



UI::UI()
{

}

void UI::UpdateInterface(Scheduler* SchedPtr, int mode) const
{

	if (mode == 1 || mode == 2)
	{
		cout << "Current Timestep " << SchedPtr->GetTimeStep() << endl;
		cout << "------------------------------- RDY Processes --------------------------\n";
		int Num_Processors = SchedPtr->GetPP();
		for (int i = 0; i < Num_Processors; i++)
		{
			cout << "Processor " << i + 1;
			if (i < SchedPtr->GetNFCFS())
				cout << " [FCFS]: ";
			else if (i < SchedPtr->GetNFCFS() + SchedPtr->GetNSJF())
				cout << " [SJF ]: ";
			else if (i < SchedPtr->GetNFCFS() + SchedPtr->GetNRR() + SchedPtr->GetNSJF())
				cout << " [RR  ]: ";
			else
				cout << " [EDF ]: ";
			SchedPtr->PrintProcessor(i);
		}
		cout << endl;
		cout << "-------------------------------BLK Processes ---------------------------\n";
		SchedPtr->PrintBLK();
		cout << "-------------------------------RUN Processes ---------------------------\n";
		cout << SchedPtr->RunningProcessors() << " RUN: ";
		bool check = false;  // check if this is the first process to print or not
		for (int i = 0; i < Num_Processors; i++)
		{
			int n = SchedPtr->GetRunningID(i);
			if (check && n > -1)
				cout << ", ";
			if (n > -1)
			{
				cout << n << "(P" << i + 1 << ")";
				check = true;
			}
		}
		cout << endl;
		cout << "-------------------------------TRM processes ---------------------------\n";
		SchedPtr->PrintTRM();
		cout << endl;
		if (mode == 1)
		{
			cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !\n\n\n";
			char ch;
			cin >> ch;
		}
		else
		{
			Sleep(1);
		}
	}
	else
	{
		cout << "Silent Mode .....     Simulation Start ......" << endl;
		cout << "Simulation ends..,Output File Created" << endl;
	}
}

int UI::ReadMode() const
{
	int n;
	cout << "1.Interactive Mode " << endl << "2.Step_By_Step Mode" << endl << "3.Silent Mode" << endl;
	cin >> n;
	return n;
}
string UI::ReadFileName() const
{
	cout << "Enter Name of the file " << endl;
	string FileName;
	cin >> FileName;
	return FileName;
}

UI::~UI()
{
}
