#include "AddWhile.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\HelperFn.h"
#include <sstream>
using namespace std;

AddWhile::AddWhile(ApplicationManager* pAppManager) : Action(pAppManager) {}


void AddWhile::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    
    pOut->PrintMessage("While Statement: Click to add the statement");
    pIn->GetPointClicked(Position);
    while (!InDrawingArea(Position))
    {
        pOut->PrintMessage("Invalid position! Click inside the drawing area.");
        pIn->GetPointClicked(Position);
    }
    pOut->ClearStatusBar();

   
    pOut->PrintMessage("Enter the LHS:");
    LHS = pIn->GetVariableOrVal(pOut);   // GetVariable يضمن اسم متغير صالح
    pOut->PrintMessage("Enter the comparison operator (==, !=, <, <=, >, >=):");
    op = pIn->GetCompOperator(pOut);      // GetCompOperator يضمن عامل صالح
    pOut->PrintMessage("Enter the RHS:");
    RHS = pIn->GetVariableOrVal(pOut);      // GetVariable يضمن اسم متغير صالح
    // Construct condition text
    ConditionText = LHS + " " + op + " " + RHS;
    pOut->ClearStatusBar();  // Clean messages after data entry
}

void AddWhile::Execute()
{
    ReadActionParameters();

    Point Corner;
    Corner.x = Position.x - UI.COND_WDTH / 2;
    Corner.y = Position.y - UI.COND_HI / 2;
    WhileStatement* pCond = new WhileStatement(Corner, ConditionText);
    pManager->AddStatement(pCond);
}
