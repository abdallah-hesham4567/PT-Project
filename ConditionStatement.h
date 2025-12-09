#pragma once
#include "Statement.h"
#include "..\GUI\Output.h"
#include <string>
using namespace std;

class ConditionStatement : public Statement
{
    string Condition;   // e.g., "x > 5"
    Statement* TrueBranch;  // pointer to the statement for the true path
    Statement* FalseBranch; // pointer to the statement for the false path (optional)

    Point LeftCorner;
    Point Inlet;
    Point OutletTrue;
    Point OutletFalse;

public:
    ConditionStatement(Point Lcorner, const string& cond);

    void setCondition(const string& cond);
    string getCondition() const { return Condition; }

    void UpdateStatementText();

    void setTrueBranch(Statement* stmt) { TrueBranch = stmt; }
    void setFalseBranch(Statement* stmt) { FalseBranch = stmt; }
    Statement* getTrueBranch() const { return TrueBranch; }
    Statement* getFalseBranch() const { return FalseBranch; }

    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsConditional() const;
    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const override { return "COND"; }
    virtual void Edit(ApplicationManager* pManager);
	virtual Statement* Clone() const;
};
