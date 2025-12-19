#include "AddOperationAssign.h"

#include "..\ApplicationManager.h"

#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\HelperFn.h"
#include <sstream>
using namespace std;
//constructor: set the ApplicationManager pointer inside this action

AddOperationAssign::AddOperationAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddOperationAssign::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	
	pOut->PrintMessage("Write: Click where to place the statement.");
	pIn->GetPointClicked(Position);

	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y - UI.ASSGN_HI / 2;

	while (!pManager->CanPlaceStatement(Corner, UI.ASSGN_WDTH, UI.ASSGN_HI))
	{
		pOut->PrintMessage("Invalid position! Click in empty drawing area.");
		pIn->GetPointClicked(Position);

		Corner.x = Position.x - UI.ASSGN_WDTH / 2;
		Corner.y = Position.y - UI.ASSGN_HI / 2;
	}
	pOut->ClearStatusBar();

	
	pOut->PrintMessage("Enter the variable name for LHS:");
	LHS = pIn->GetVariable(pOut);   // check lhs
	
	pOut->PrintMessage("Enter the first operand for RHS:");
	RHS1 = pIn->GetVariableOrVal(pOut);      // can be var or value
	
	pOut->PrintMessage("Enter the operator (+, -, *, /):");
	op = pIn->GetArithOperator(pOut);      // GetOperator
	
	pOut->PrintMessage("Enter the second operand for RHS:");
	RHS2 = pIn->GetVariableOrVal(pOut);      // can be var or value
	pOut->ClearStatusBar();  
}

void AddOperationAssign::Execute()
{
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y - UI.ASSGN_HI /2 ;
	OperatorAssignment* pAssign = new OperatorAssignment(Corner, LHS, op, RHS1, RHS2);
	pManager->AddStatement(pAssign);
}




