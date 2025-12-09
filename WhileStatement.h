#pragma once
#include "Statement.h"
#include "..\Defs.h"
#include "..\GUI\Output.h"
#include <string>
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

public:
    WhileStatement(Point Lcorner, const string& cond);

    void setCondition(const string& cond);
    string getCondition() const { return Condition; }

    void UpdateStatementText();
    virtual void Draw(Output* pOut) const;

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
	virtual void Edit(ApplicationManager* pManager);

};
