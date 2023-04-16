#include "UI.h"
UI::UI()
{

}

void UI::UpdateInterface(Scheduler* SchedPtr,int count)
{
	cout << "Current Timestep:" << count << endl;
	cout << "------------------------------- RDY Processes ------------------\n";
	SchedPtr->PrintProcessor();
	cout << "-------------BLK Processes ---------------------------\n";
	SchedPtr->PrintBLK();
	cout << "--------------- RUN Processes --------------------------\n";
	cout << SchedPtr->RunningProcessors() << " RUN: ";
	SchedPtr->PrintRUN();
	cout << endl;
	cout << "-------------------- TRM processes -----------------------\n";
	SchedPtr->PrintTRM();
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

