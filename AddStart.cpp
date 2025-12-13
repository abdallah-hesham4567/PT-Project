#include "AddStart.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

AddStart::AddStart(ApplicationManager* pAppManager) : Action(pAppManager) {}

void AddStart::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Write: Click where to place the statement.");
    pIn->GetPointClicked(Position);

    Point Corner;
    Corner.x = Position.x - UI.START_END_WDTH / 2;
    Corner.y = Position.y - UI.START_END_HI / 2;

    while (!pManager->CanPlaceStatement(Corner, UI.START_END_WDTH, UI.START_END_HI))
    {
        pOut->PrintMessage("Invalid position! Click in empty drawing area.");
        pIn->GetPointClicked(Position);

        Corner.x = Position.x - UI.START_END_WDTH / 2;
        Corner.y = Position.y - UI.START_END_HI / 2;
    }
    pOut->ClearStatusBar();
}

void AddStart::Execute()
{ 

    ReadActionParameters();
    Start* pStart = new Start(Position);
    pManager->AddStatement(pStart);
}