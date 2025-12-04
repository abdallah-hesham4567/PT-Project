#include "AddDeclare.h"
#include "..\ApplicationManager.h"
#include "..\GUI/Input.h"
#include "..\GUI/Output.h"
#include <sstream>
using namespace std;

AddDeclare::AddDeclare(ApplicationManager* pApp) : Action(pApp) {}

void AddDeclare::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    // Click position
    pOut->PrintMessage("Click to add variable declaration");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // Get variable name
    pOut->PrintMessage("Enter variable name:");
    VariableName = pIn->GetVariable(pOut); // your function to ensure valid name

    // Ask if initialized
    pOut->PrintMessage("Do you want to assign a value? (y/n)");
    string choice = pIn->GetVariable(pOut);
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
    Corner.y = Position.y;

    DeclareStatement* pDecl = new DeclareStatement(Corner, VariableName, HasValue, Value);
    pManager->AddStatement(pDecl);
}
