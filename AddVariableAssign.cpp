#include "AddVariableAssign.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\HelperFn.h"
#include <sstream>
#include "VariableAssign.h"
using namespace std;

//constructor: set the ApplicationManager pointer inside this action	
AddVariableAssign::AddVariableAssign(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddVariableAssign::ReadActionParameters()
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
	LHS = pIn->GetVariable(pOut);   // GetVariable 
	pOut->PrintMessage("Enter the variable name for RHS:");
	RHS = pIn->GetVariable(pOut);      // GetVariable
	pOut->ClearStatusBar();  //clear 
}
void AddVariableAssign::Execute()
{
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y - UI.ASSGN_HI / 2;
	VariableAssign* pAssign = new VariableAssign(Corner, LHS, RHS);

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}