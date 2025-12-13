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

    pOut->PrintMessage("Write: Click where to place the statement.");
    pIn->GetPointClicked(Position);

    Point Corner;
    Corner.x = Position.x - UI.READ_WDTH / 2;
    Corner.y = Position.y - UI.READ_HI / 2;

    while (!pManager->CanPlaceStatement(Corner, UI.READ_WDTH, UI.READ_HI ))
    {
        pOut->PrintMessage("Invalid position! Click in empty drawing area.");
        pIn->GetPointClicked(Position);

        Corner.x = Position.x - UI.READ_WDTH / 2;
        Corner.y = Position.y - UI.READ_HI / 2;
    }
    pOut->ClearStatusBar();

    pOut->PrintMessage("Enter variable name to read into:");
    VarName = pIn->GetVariable(pOut);

    pOut->ClearStatusBar();
}

void AddRead::Execute()
{
    ReadActionParameters();

    Point Corner;
    Corner.x = Position.x - UI.READ_WDTH / 2;
    Corner.y = Position.y - UI.READ_HI /2 ;

    Read* pRead = new Read(Corner, VarName);

    pManager->AddStatement(pRead);
}