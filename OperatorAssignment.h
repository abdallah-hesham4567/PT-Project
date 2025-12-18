#pragma once

#include "Statement.h"
#include "..//GUI//Input.h"
#include "HelperFn.h"
#include <sstream>
#include "ApplicationManager.h"

using namespace std;
class OperatorAssignment : public Statement
{
	string LHS;
	char Op;
	string RHS1;
	string RHS2;
	
	Connector* pOutConn;
	Point Inlet;
	Point Outlet;
	Point LeftCorner;
	Point Center;

	public:

	OperatorAssignment(Point Lcorner, string LeftHS="", char Oper=' ', string RHS1="", string RHS2="");
	
	void setLHS(const string& L);
	void setRHS1(const string R);
	void setRHS2(const string R);
	
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

	virtual void Edit(Input* pIn, Output* pOut);
	virtual Statement* Clone() const;
	
	virtual void SetPosition(Point p) override;

	virtual Point GetPosition() const override;
	virtual int GetWidth() const override;
	virtual int GetHeight() const override;

	virtual void Execute(Variable vars[], int& varCount, Input* pIn, Output* pOut);

};

