#pragma once
#include "ValueAssign.h"
#include <sstream>
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"


using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
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



void ValueAssign::setLHS(const string& L)
{

	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}

void ValueAssign::SetPosition(Point p)
{
	LeftCorner = p;

}

void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssignAndDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

void ValueAssign::Edit(Input* pIn, Output* pOut)
{
	pOut->PrintMessage("Editing Value Assignment Statement: Enter new LHS variable name:");
	string newLHS = pIn->GetVariable(pOut);
	if (newLHS.empty()) // User cancelled
	{
		pOut->PrintMessage("Edit cancelled.");
		return;
	}
	pOut->PrintMessage("Enter new RHS value:");
	double newRHS;
	newRHS = pIn->GetValue(pOut);
	bool validRHS = true; // Assume valid if GetValue returns a double; add validation if needed
	if (!validRHS) // User cancelled or invalid input
	{
		pOut->PrintMessage("Edit cancelled or invalid RHS value.");
		return;
	}
	LHS = newLHS;
	RHS=newRHS;
	UpdateStatementText();
	pOut->PrintMessage("Value Assignment Statement edited successfully.");
}



Statement* ValueAssign::Clone() const
{
	ValueAssign* copy = new ValueAssign(*this);
	//copy->SetOutConn(nullptr); // Reset the outgoing connector for the cloned statement
	return copy;
}

Point ValueAssign::GetPosition() const
{
	return LeftCorner;
}

int ValueAssign::GetWidth() const
{
	return UI.ASSGN_WDTH;
}

int ValueAssign::GetHeight() const
{
	return UI.ASSGN_HI;
}

void ValueAssign::Execute(Variable vars[], int& varCount, Input*, Output*)
{
	for (int i = 0; i < varCount; i++)
	{
		if (vars[i].name == LHS)
		{
			vars[i].value = RHS;
			return;
		}
	}
}



//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

Point ValueAssign::GetOutletPoint(int branch) const
{
	// Rectangle - outlet at bottom center
	return Point(Outlet.x,
		Outlet.y);
}

Point ValueAssign::GetInletPoint() const
{
	// Rectangle - inlet at top center
	return Point(Inlet.x,
		Inlet.y);
}

int ValueAssign::GetExpectedOutConnCount() const
{
	return 1; // Normal statement has 1 output
}

bool ValueAssign::IsPointInside(Point p) const
{
	return (p.x >= LeftCorner.x &&
		p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
		p.y >= LeftCorner.y &&
		p.y <= LeftCorner.y + UI.ASSGN_HI);
}


void ValueAssign::Save(ofstream& OutFile) const
{
	OutFile << "VALUE_ASSIGN\t" << ID << "\t"
		<< LeftCorner.x << "\t" << LeftCorner.y << "\t"
		<< LHS <<"\t" << RHS << endl;
}

void ValueAssign::Load(ifstream& InFile)
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

