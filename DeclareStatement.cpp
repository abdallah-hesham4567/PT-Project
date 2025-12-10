#include "DeclareStatement.h"
#include "..\GUI\Output.h"
#include <sstream>
#include "..\ApplicationManager.h"
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
	Center.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Center.y = LeftCorner.y + UI.ASSGN_HI / 2;
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




Point DeclareStatement::GetOutletPoint(int branch) const
{
    // Rectangle - outlet at bottom center
    return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
        LeftCorner.y + UI.ASSGN_HI);
}

Point DeclareStatement::GetInletPoint() const
{
    // Rectangle - inlet at top center
    return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
        LeftCorner.y);
}

int DeclareStatement::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool DeclareStatement::IsPointInside(Point p) const
{
    return (p.x >= LeftCorner.x &&
        p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.ASSGN_HI);
}

void DeclareStatement::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Edit Declare Statement - enter variable name:");
    string newVar = pIn->GetVariable(pOut);
    setVariable(newVar);
	pOut->PrintMessage("Do you want to initialize it? (OK/NO THANKS)");
    string choice = pIn->GetString(pOut);
    if (choice == "OK"||choice=="Ok"||choice=="ok")
    {
        pOut->PrintMessage("Enter initial value:");
        double val = pIn->GetValue(pOut);
        setValue(val);
    }
    else
    {
        HasValue = false;
        UpdateStatementText();
    }
	pOut->ClearStatusBar();
}

Statement* DeclareStatement::Clone() const
{
	return new DeclareStatement(*this);
}

void DeclareStatement::Save(ofstream& OutFile) const
{
    OutFile << "DECLARE\t" << ID << "\t" << Center.x << "\t"
        << Center.y << "\t" << VariableName << "\n";
}


void DeclareStatement::Load(ifstream& InFile)
{
    InFile >> ID >> Center.x >> Center.y >> VariableName;
    UpdateBoundingBox();
}








