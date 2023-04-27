#include "UI.h"
UI::UI()
{

}

void UI::UpdateInterface(Scheduler* SchedPtr)
{
	cout << "Current Timestep " << SchedPtr->GetTimeStep() << endl;
	cout << "------------------------------- RDY Processes --------------------------\n";
	int Num_Processors = SchedPtr->GetNFCFS() + SchedPtr->GetNRR() + SchedPtr->GetNSJF();
	for (int i = 0; i < Num_Processors; i++)
	{
		cout << "Processor " <<i+1;
		if (i < SchedPtr->GetNFCFS())
			cout << " [FCFS]: ";
		else if (i < SchedPtr->GetNFCFS() + SchedPtr->GetNSJF())
			cout << " [SJF ]: ";
		else
			cout << " [RR  ]: ";
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
		int n=SchedPtr->GetRunningID(i);
		if (check&& n>-1)
			cout << ", ";
		if (n > -1)
		{
			cout << n << "(P" << i+1 << ")";
			check = true;
		}
	}
	cout << endl;
	cout << "-------------------------------TRM processes ---------------------------\n";
	SchedPtr->PrintTRM();
	cout << endl;
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !\n\n\n";
	///cin from the user the mode of output 
	///// print RTM
	// Print BLK
	//// print RUN 
}

int UI::ReadMode()
{
	int n;
	cout << "1.Interactive Mode " << endl << "2.Step_By_Step Mode" << endl << "3.Silent Mode" << endl;
	cin >> n;
	return n;
}
string UI::ReadFileName()
{
	cout << "Enter Name of the file " << endl;
	string FileName;
	cin >> FileName;
	return FileName;
}

