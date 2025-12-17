#pragma once
#include "Statement.h"
#include "..\Defs.h"
#include "..\GUI\Output.h"
#include <string>
#include "../AddWhile.h"
using namespace std;

class WhileStatement : public Statement 
{
    string Condition;       // شرط اللوب
    Connector* TrueBranch;  // لو الشرط صح
    Connector* FalseBranch; // لو الشرط غلط
    Point Inlet;
    Point OutletTrue;
    Point OutletFalse;
    Point LeftCorner;
    CompOperator Comp;
    string op;
    string RHS;
    string LHS;
    Point Center;

public:
    WhileStatement(Point Lcorner, const string& LHS="", const string& OP="", const string& RHS="");


    void setCondition(const string& cond);
    string getCondition() const { return Condition; }

    void UpdateStatementText();
  

    void setTrueBranch(Connector* conn) { TrueBranch = conn; }
    void setFalseBranch(Connector* conn) { FalseBranch = conn; }
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
    string getStatementType() const override;
    virtual void Edit(Input* pIn, Output* pOut);
    virtual Statement* Clone() const ;

    virtual void SetPosition(Point p);

	virtual Point GetPosition() const;
	virtual int GetWidth() const;
	virtual int GetHeight() const;

};
