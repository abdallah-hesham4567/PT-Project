#pragma once
#include "Statement.h"
#include "..\GUI\Output.h"
#include <string>
using namespace std;

class ConditionStatement : public Statement
{
    string Condition;   
    Connector* TrueBranch;  // true branch
	Connector* FalseBranch; // false statement

    Point LeftCorner;
    Point Inlet;
    Point OutletTrue;
    Point OutletFalse;
    Point Center;
    string op;
    string RHS;
    string LHS;

public:
    ConditionStatement(Point Lcorner, const string& LHS="", const string& OP="", const string& RHS="");
    
    void setCondition(const string& cond);
    string getCondition() const { return Condition; }

    void UpdateStatementText();

    void setTrueBranch(Connector* Conn) { TrueBranch = Conn; }
    void setFalseBranch(Connector* Conn) { FalseBranch = Conn; }
    Connector* getTrueBranch() const { return TrueBranch; }
    Connector* getFalseBranch() const { return FalseBranch; }

    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsConditional() const;
    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const;
	string GetLHS() const { return LHS; }
	string GetRHS() const { return RHS; }
    virtual void Edit(Input* pIn, Output* pOut);
	virtual Statement* Clone() const;

    virtual void SetPosition(Point p);
	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;
	virtual void Execute(Variable vars[], int& varCount, Input* pIn, Output* pOut){}
    bool Evaluate(Variable vars[], int varCount);


};
