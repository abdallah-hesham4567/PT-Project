#include "Run.h"

void Run::ReadActionParameters()
{
	//No parameters to read
}

void Run::Execute()
{
   // if (!pManager->Validate())
   // {
   //     pManager->GetOutput()->PrintMessage("Flowchart is not valid");
   //     return;
   // }

    pManager->RunSimulation();
}

