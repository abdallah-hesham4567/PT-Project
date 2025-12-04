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

    // 1️⃣ Click position
    pOut->PrintMessage("Condition Statement: Click to add the statement");
    pIn->GetPointClicked(Position);
    pOut->ClearStatusBar();

    // 2️⃣ Get condition text from user
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
    Corner.y = Position.y;

    ConditionStatement* pCond = new ConditionStatement(Corner, ConditionText);
    pManager->AddStatement(pCond);
}
