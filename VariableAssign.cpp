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
string VariableAssign::GetLHS() const
{
	return LHS;
}
string VariableAssign::GetRHS() const
{
	return RHS;
}
void VariableAssign::Draw(Output* pOut) const
{
	
	pOut->DrawAssignAndDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

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
	return Outlet;
}

Point VariableAssign::GetInletPoint() const
{
	// Rectangle - inlet at top center
	return Inlet;
}

int VariableAssign::GetExpectedOutConnCount() const
{
	return 1;                                   // Normal statement has 1 output
}

bool VariableAssign::IsPointInside(Point p) const
{
	return (p.x >= LeftCorner.x &&
		p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		p.y >= LeftCorner.y &&
		p.y <= LeftCorner.y + UI.ASSGN_HI);
}
void VariableAssign::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Editing Variable Assignment Statement: Enter new LHS variable name:");
	string newLHS = pIn->GetVariable(pOut);
	pOut->PrintMessage("Editing Variable Assignment Statement: Enter new RHS variable name:");
	string newRHS = pIn->GetVariable(pOut);
	// Update LHS and RHS
	LHS = newLHS;
	RHS = newRHS;
	UpdateStatementText();
	pOut->ClearStatusBar();
}

string VariableAssign::GetVariableName() const
{
	return ;
}

Statement* VariableAssign::Clone() const
{
	VariableAssign* newVarAssign = new VariableAssign(*this);
	newVarAssign->SetOutConn(nullptr);
	return newVarAssign;
}

Point VariableAssign::GetPosition() const
{
	return LeftCorner;
}


int VariableAssign::GetWidth() const
{
	return UI.ASSGN_WDTH;
}

int VariableAssign::GetHeight() const
{
	return UI.ASSGN_HI;
}

void VariableAssign::Execute(Variable vars[], int& varCount, Input*, Output*)
{
	double rhsValue = 0;

	for (int i = 0; i < varCount; i++)
		if (vars[i].name == RHS)
			rhsValue = vars[i].value;

	for (int i = 0; i < varCount; i++)
		if (vars[i].name == LHS)
			vars[i].value = rhsValue;
}



void VariableAssign::Save(ofstream& OutFile) const
{
	OutFile << "VAR_ASSIGN\t" << ID << "\t"
		<< LeftCorner.x << "\t" << LeftCorner.y << "\t"
		<< LHS << "\t" << RHS << endl;
}

void VariableAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	Center.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Center.y = LeftCorner.y + UI.ASSGN_HI / 2;
	UpdateStatementText();
}


void VariableAssign::SetPosition(Point p)
{
	LeftCorner.x = p.x - UI.ASSGN_WDTH / 2;
	LeftCorner.y = p.y - UI.ASSGN_HI /2;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

	Center.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Center.y = LeftCorner.y + UI.ASSGN_HI / 2;
}

