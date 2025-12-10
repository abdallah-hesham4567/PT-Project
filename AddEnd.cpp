#include "AddEnd.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "End.h"
AddEnd::AddEnd(ApplicationManager* pAppManager) : Action(pAppManager) {}

void AddEnd::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click where you want to place the End.");
    pIn->GetPointClicked(Position);
    while (!InDrawingArea(Position))
    {
        pOut->PrintMessage("Invalid position! Click inside the drawing area.");
        pIn->GetPointClicked(Position);
    }
    pOut->ClearStatusBar();
}

void AddEnd::Execute()
{
    ReadActionParameters();
    End* pEnd = new End(Position);
    pManager->AddStatement(pEnd);
}