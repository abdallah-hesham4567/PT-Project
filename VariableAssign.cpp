#pragma once
#include "VariableAssign.h"
#include <sstream>
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\Actions\Action.h"
#include "..\ApplicationManager.h"
using namespace std;
VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddVariableAssign) action
	//       before passing it to the constructor of VariableAssign
	LHS = LeftHS;
	RHS = RightHS;
	UpdateStatementText();
	LeftCorner = Lcorner;
	pOutConn = NULL;	//No connectors yet
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	Center.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Center.y = LeftCorner.y + UI.ASSGN_HI / 2;
}
void VariableAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VariableAssign::setRHS(const string& R)
{
	RHS = R;
	UpdateStatementText();
}
void VariableAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssignAndDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}
//This function should be called when LHS or RHS changes
void VariableAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

Point VariableAssign::GetOutletPoint(int branch) const
{
	// Rectangle - outlet at bottom center
	return Point(Outlet.x,
		Outlet.y);
}

Point VariableAssign::GetInletPoint() const
{
	// Rectangle - inlet at top center
	return Point(Inlet.x,
		Inlet.y);
}

int VariableAssign::GetExpectedOutConnCount() const
{
	return 1; // Normal statement has 1 output
}

bool VariableAssign::IsPointInside(Point p) const
{
	return (p.x >= LeftCorner.x &&
		p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		p.y >= LeftCorner.y &&
		p.y <= LeftCorner.y + UI.ASSGN_HI);
}
void VariableAssign::Edit()
{
	ApplicationManager* pManager;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Editing Variable Assignment Statement: Enter new LHS variable name:");
	string newLHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Editing Variable Assignment Statement: Enter new RHS variable name:");
	string newRHS = pIn->GetVariable(pOut);
	// Update LHS and RHS
	LHS = newLHS;
	RHS = newRHS;
	pOut->ClearStatusBar();
}

Statement* VariableAssign::Clone() const
{
	VariableAssign* newVarAssign = new VariableAssign(*this);
	newVarAssign->SetOutConn(nullptr);
	return newVarAssign;
}


void VariableAssign::Save(ofstream& OutFile) const
{
	OutFile << "DECLARE\t" << ID << "\t"
		<< Center.x << "\t" << Center.y << "\t"
		<< LHS << endl;
}

void VariableAssign::Load(ifstream& InFile)
{
	InFile >> ID >> Center.x >> Center.y >> LHS;
}

