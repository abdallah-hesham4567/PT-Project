#pragma once

#include "Statement.h"
#include "..//GUI//Input.h"
#include "HelperFn.h"
#include <sstream>
#include "ApplicationManager.h"

using namespace std;
class OperatorAssignment : public Statement
{
	ArithOperator Opp;
	string LHS;
	string RHS1;
	string RHS2;
	string Op;
	Connector* pOutConn;
	Point Inlet;
	Point Outlet;
	Point LeftCorner;
	Point Center;
	public:

	OperatorAssignment(Point Lcorner, string LeftHS, string Oper, string RHS1 , string RHS2 );
	void setLHS(const string& L);
	void setRHS1(const string R);
	void setRHS2(const string R);
	virtual void Draw(Output* pOut) const;
	void setOp(char O);
	virtual void UpdateStatementText();

	virtual Point GetOutletPoint(int branch = 0) const;
	virtual Point GetInletPoint() const;
	virtual int GetExpectedOutConnCount() const;
	virtual bool IsPointInside(Point p) const;

	virtual void Draw(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const;
	virtual void Load(ifstream& InFile);
	string getStatementType() const override { return "OP_ASSIGN"; }

	virtual void Edit(ApplicationManager* pManager);
	virtual Statement* Clone() const;
	


};

