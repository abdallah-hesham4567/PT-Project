#include "AddStart.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

AddStart::AddStart(ApplicationManager* pAppManager) : Action(pAppManager) {}

void AddStart::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click where you want to place the Start.");
    pIn->GetPointClicked(Position);
    while (!InDrawingArea(Position))
    {
        pOut->PrintMessage("Invalid position! Click inside the drawing area.");
        pIn->GetPointClicked(Position);
    }
    pOut->ClearStatusBar();
}

void AddStart::Execute()
{
    ReadActionParameters();
    Start* pStart = new Start(Position);
    pManager->AddStatement(pStart);
}