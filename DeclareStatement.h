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

public:
    DeclareStatement(Point Lcorner, const string& var, bool hasVal = false, double val = 0);

    void setVariable(const string& var);
    void setValue(double val);
    string getVariable() const { return VariableName; }
    bool hasValue() const { return HasValue; }
    double getValue() const { return Value; }

    void UpdateStatementText();  // Create text like "x = 5" or "y"
    virtual void Draw(Output* pOut) const;
};
