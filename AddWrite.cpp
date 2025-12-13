#include "AddWrite.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include    <string>
#include "Write.h"
using namespace std;

AddWrite::AddWrite(ApplicationManager* pAppManager) : Action(pAppManager) {}

void AddWrite::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Write: Click where to place the statement.");
    pIn->GetPointClicked(Position);

    Point Corner;
    Corner.x = Position.x - UI.WRITE_WDTH / 2;
    Corner.y = Position.y - UI.WRITE_HI / 2;

    while (!pManager->CanPlaceStatement(Corner, UI.WRITE_WDTH, UI.WRITE_HI))
    {
        pOut->PrintMessage("Invalid position! Click in empty drawing area.");
        pIn->GetPointClicked(Position);

        Corner.x = Position.x - UI.WRITE_WDTH / 2;
        Corner.y = Position.y - UI.WRITE_HI / 2;
    }
    
    pOut->ClearStatusBar();

    pOut->PrintMessage("Enter expression or text to write:");
    Expr = pIn->GetString(pOut);

    pOut->ClearStatusBar();
}

void AddWrite::Execute()
{
    ReadActionParameters();

    Point Corner;
    Corner.x = Position.x - UI.WRITE_WDTH / 2;
    Corner.y = Position.y - UI.WRITE_HI /2 ;

    Write* pWrite = new Write(Corner, Expr);

    pManager->AddStatement(pWrite);
}