#include "AddCondition.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\HelperFn.h"
#include <sstream>
using namespace std;

AddCondition::AddCondition(ApplicationManager* pAppManager) : Action(pAppManager) {}


void AddCondition::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    
    pOut->PrintMessage("Write: Click where to place the statement.");
    pIn->GetPointClicked(Position);

    Point Corner;
    Corner.x = Position.x - UI.COND_WDTH / 2;
    Corner.y = Position.y - UI.COND_HI / 2;

    while (!pManager->CanPlaceStatement(Corner, UI.COND_WDTH, UI.COND_HI))
    {
        pOut->PrintMessage("Invalid position! Click in empty drawing area.");
        pIn->GetPointClicked(Position);

        Corner.x = Position.x - UI.COND_WDTH / 2;
        Corner.y = Position.y - UI.COND_HI / 2;
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


void AddCondition::Execute()
{
    ReadActionParameters();

    Point Corner;
    Corner.x = Position.x - UI.COND_WDTH / 2;
    Corner.y = Position.y - UI.COND_HI/2;

    ConditionStatement* pCond = new ConditionStatement(Corner, LHS,op,RHS);
    pManager->AddStatement(pCond);
}
