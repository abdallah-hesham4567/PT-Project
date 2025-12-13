#include "AddDeclare.h"
#include "..\ApplicationManager.h"
#include "..\GUI/Input.h"
#include "..\GUI/Output.h"
#include <sstream>
using namespace std;

AddDeclare::AddDeclare(ApplicationManager* pApp) : Action(pApp) { }

void AddDeclare::ReadActionParameters()
{
    HasValue = false;
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Click position
    pOut->PrintMessage("Write: Click where to place the statement.");
    pIn->GetPointClicked(Position);

    Point Corner;
    Corner.x = Position.x - UI.ASSGN_WDTH / 2;
    Corner.y = Position.y - UI.ASSGN_HI / 2;

    while (!pManager->CanPlaceStatement(Corner, UI.ASSGN_WDTH, UI.ASSGN_HI))
    {
        pOut->PrintMessage("Invalid position! Click in empty drawing area.");
        pIn->GetPointClicked(Position);

        Corner.x = Position.x - UI.ASSGN_WDTH   / 2;
        Corner.y = Position.y - UI.ASSGN_HI / 2;
    }
    pOut->ClearStatusBar();
    string choice;
    // Get variable name
   // pOut->PrintMessage("Enter variable name:");
    VariableName = pIn->GetVariable(pOut); // your function to ensure valid name
    // Ask if initialized
    choice = pIn->GetChoice(pOut);
    if (choice == "y" || choice == "Y")
    {
        HasValue = true;
        pOut->PrintMessage("Enter value:");
        Value = pIn->GetValue(pOut);
    }

    else
        HasValue = false;

    pOut->ClearStatusBar();
}

void AddDeclare::Execute()
{
    ReadActionParameters();

    Point Corner;
    Corner.x = Position.x - UI.ASSGN_WDTH / 2;
    Corner.y = Position.y - UI.ASSGN_HI /2;

    DeclareStatement* pDecl = new DeclareStatement(Corner, VariableName, HasValue, Value);
    pManager->AddStatement(pDecl);
}
