#include "ActionSave.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include <fstream>

ActionSave::ActionSave(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void ActionSave::ReadActionParameters()
{
    // Get pointer to the input and output interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Print message to status bar asking user to enter filename
    pOut->PrintMessage("Save Flowchart: Enter filename to save");

    // Read filename from user
    FileName = pIn->GetString(pOut);

    // Clear status bar
    pOut->ClearStatusBar();
}

void ActionSave::Execute()
{
    // Read action parameters (filename)
    ReadActionParameters();

    // Create and open the output file stream
    ofstream OutFile(FileName + ".txt");

    if (!OutFile.is_open())
    {
        Output* pOut = pManager->GetOutput();
        pOut->PrintMessage("Error: Cannot create/open file for saving!");
        return;
    }

    // Call ApplicationManager to save all statements and connectors
    pManager->SaveAll(OutFile);

    // Close the file
    OutFile.close();

    // Print success message
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Flowchart saved successfully to " + FileName + ".txt");
}
