#pragma once
#include "ValueAssign.h"
#include <sstream>
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"



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


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssignAndDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
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
	return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
		LeftCorner.y + UI.ASSGN_HI);
}

Point ValueAssign::GetInletPoint() const
{
	// Rectangle - inlet at top center
	return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
		LeftCorner.y);
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

