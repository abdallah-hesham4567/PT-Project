#include "DeclareStatement.h"
#include "..\GUI\Output.h"
#include <sstream>
using namespace std;

DeclareStatement::DeclareStatement(Point Lcorner, const string& var, bool hasVal, double val)
{
    LeftCorner = Lcorner;
    VariableName = var;
    HasValue = hasVal;
    Value = val;

    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;

    UpdateStatementText();
}

void DeclareStatement::setVariable(const string& var)
{
    VariableName = var;
    UpdateStatementText();
}

void DeclareStatement::setValue(double val)
{
    Value = val;
    HasValue = true;
    UpdateStatementText();
}

void DeclareStatement::UpdateStatementText()
{
    if (HasValue)
        Text = VariableName + " = " + to_string(Value);
    else
        Text = VariableName;
}

void DeclareStatement::Draw(Output* pOut) const
{
    pOut->DrawAssignAndDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}


