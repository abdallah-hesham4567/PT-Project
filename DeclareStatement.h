#pragma once
#include "Statement.h"
#include "..\Defs.h"
#include <string>
using namespace std;

class DeclareStatement : public Statement
{
    string VariableName;
    double Value;
    bool HasValue;     // true if initialization like x = 5
    Point LeftCorner;
    Point Inlet;
    Point Outlet;
	Point Center;

public:
    DeclareStatement(Point Lcorner, const string& var, bool hasVal = false, double val = 0);

    void setVariable(const string& var);
    void setValue(double val);
    string getVariable() const { return VariableName; }
    bool hasValue() const { return HasValue; }
    double getValue() const { return Value; }

    void UpdateStatementText();  // Create text like "x = 5" or "y"
    virtual Point GetOutletPoint(int branch = 0) const;
    virtual Point GetInletPoint() const;
    virtual int GetExpectedOutConnCount() const;
    virtual bool IsPointInside(Point p) const;

    virtual void Draw(Output* pOut) const;
    virtual void Save(ofstream& OutFile) const;
    virtual void Load(ifstream& InFile);
    string getStatementType() const override { return "DECLARE"; }
    virtual void Edit();
	virtual Statement* Clone() const;
    
    virtual void SetPosition(Point p);
};
