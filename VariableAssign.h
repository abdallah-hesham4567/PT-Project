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
	Connector* pOutConn;	//Variable Assignment Stat. has one Connector to next statement
	//Each statement type in flowchart has a predefined number of (output) connectors
	//For example, conditional statement always has 2 output connectors
	//Note: We don't need to keep track with input connectors
	//      Whenever we want to iterate on all statements of the flowchart
	//      we will begin with start statement then its output connector
	//      then the connector's destination statement and so on (follow the connectors)
	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector
	Point LeftCorner;	//left corenr of the statement block.
	Point Center;
	virtual void UpdateStatementText();
public:
	VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");
	
	void setLHS(const string& L);
	void setRHS(const string& R);

	virtual Point GetOutletPoint(int branch = 0) const;
	virtual Point GetInletPoint() const;
	virtual int GetExpectedOutConnCount() const;
	virtual bool IsPointInside(Point p) const;

	virtual void SetPosition(Point p);

	virtual void Draw(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const;
	virtual void Load(ifstream& InFile);
	virtual void Edit(Input* pIn, Output* pOut);
	virtual string getStatementType()const;
	virtual Statement* Clone() const;
	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual void Execute(Variable vars[], int& varCount, Input* pIn, Output* pOut);
};
#endif
