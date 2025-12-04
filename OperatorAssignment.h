#pragma once

#include "Statement.h"
#include "..//GUI//Input.h"
#include "HelperFn.h"
#include <sstream>

using namespace std;
class OperatorAssignment : public Statement
{
	string LHS;
	string RHS1;
	string RHS2;
	string Op;
	Connector* pOutConn;
	Point Inlet;
	Point Outlet;
	Point LeftCorner;
	public:

	OperatorAssignment(Point Lcorner, string LeftHS, string Oper, string RHS1 , string RHS2 );
	void setLHS(const string& L);
	void setRHS1(const string R);
	void setRHS2(const string R);
	virtual void Draw(Output* pOut) const;
	void setOp(char O);
	virtual void UpdateStatementText();
	


};

