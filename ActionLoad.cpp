#include "ActionLoad.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <fstream>

ActionLoad::ActionLoad(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void ActionLoad::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMessage("Load Flowchart: Enter filename to load");
    FileName = pIn->GetString(pOut);
    pOut->ClearStatusBar();
}

void ActionLoad::Execute()
{
    // Read filename
    ReadActionParameters();

    // Open file
    ifstream InFile(FileName + ".txt");

    if (!InFile.is_open())
    {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Error: Cannot open file for loading!");
        return;
    }

    // Call ApplicationManager to load everything
    pManager->LoadAll(InFile);

    // Close file
    InFile.close();

    // Show success message
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Flowchart loaded successfully from " + FileName + ".txt");

    // Update interface to show loaded flowchart
    pManager->UpdateInterface();
}