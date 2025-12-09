#include "AddRead.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

using namespace std;

AddRead::AddRead(ApplicationManager* pAppManager) : Action(pAppManager) {}

void AddRead::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Read: Click where to place the statement.");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    pOut->PrintMessage("Enter variable name to read into:");
    VarName = pIn->GetVariable(pOut);

    pOut->ClearStatusBar();
}

void AddRead::Execute()
{
    ReadActionParameters();

    Point Corner;
    Corner.x = Position.x - UI.IO_WDTH / 2;
    Corner.y = Position.y;

    Read* pRead = new Read(Corner, VarName);

    pManager->AddStatement(pRead);
}