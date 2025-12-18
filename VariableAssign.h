#ifndef Variable_ASSIGN_H
#define Variable_ASSIGN_H
#include "Statement.h"
//Variable Assignment statement class
//The variable assignment statement assigns a variable to another variable
class VariableAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (name of a variable)
	Connector* pOutConn;	     //Variable Assignment Stat. has one Connector to next statement
	
	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector
	Point LeftCorner;	//left corenr of the statement block.
	Point Center;        //Center Point of the shape

public:
	VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");
	
	void setLHS(const string& L);
	void setRHS(const string& R);

	virtual Point GetOutletPoint(int branch = 0) const;
	virtual Point GetInletPoint() const;
	virtual int GetExpectedOutConnCount() const;

	virtual bool IsPointInside(Point p) const;

	virtual void SetPosition(Point p);
	virtual Point GetPosition() const;
	virtual void Draw(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const;
	virtual void Load(ifstream& InFile);
	virtual void Edit(Input* pIn, Output* pOut);
	virtual string getStatementType() const { return "VAR_ASSIGN"; }

	virtual Statement* Clone() const;
	
	virtual int GetWidth() const;
	virtual int GetHeight() const;

	virtual void Execute(Variable vars[], int& varCount, Input* pIn, Output* pOut);    //used in run
	virtual void UpdateStatementText();    //to update text
};
#endif
