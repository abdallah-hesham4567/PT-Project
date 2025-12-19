#ifndef VALUE_ASSIGN_H
#define VALUE_ASSIGN_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class ValueAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	double RHS;	//Right Handside (Value)

	Connector* pOutConn;	

	Point Inlet;	//A point where connections enters this statement 

	Point Outlet;	//A point a connection leaves this statement

	Point Center;	//Center point of the statement block
	Point LeftCorner;	//left corenr of the statement block.

	

public:
	ValueAssign(Point Lcorner, string LeftHS = "", double RightHS = 0);
	
	void setLHS(const string& L);
	void setRHS(double R);
	string GetLHS() const { return LHS; }
	string GetRHS() const { return to_string(RHS); }

	virtual void SetPosition(Point p);

	
	virtual void UpdateStatementText();

	virtual Point GetOutletPoint(int branch = 0) const;
	virtual Point GetInletPoint() const;
	virtual int GetExpectedOutConnCount() const;
	virtual bool IsPointInside(Point p) const;

	virtual void Draw(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const ;
	virtual void Load(ifstream& InFile);
	virtual void Edit(Input* pIn, Output* pOut);
	virtual string getStatementType() const { return "VALASSIGN"; }
	virtual Statement* Clone() const;
	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual void Execute(Variable vars[], int& varCount, Input* pIn, Output* pOut);
};

#endif