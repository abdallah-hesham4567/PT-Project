#include "Read.h"
#include <sstream>
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

using namespace std;

Read::Read(Point Lcorner, const string& var)
{
    VarName = var;
    LeftCorner = Lcorner;

    pOutConn = NULL;

    Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.READ_HI;
	Center.x = LeftCorner.x + UI.READ_WDTH / 2;
	Center.y = LeftCorner.y + UI.READ_HI / 2;
    UpdateStatementText();
}

void Read::SetPosition(Point p)
{
    LeftCorner.x = p.x - UI.READ_WDTH / 2;
    LeftCorner.y = p.y;

    Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.READ_HI;

    Center.x = LeftCorner.x + UI.READ_WDTH / 2;
    Center.y = LeftCorner.y + UI.READ_HI / 2;
}

void Read::setVarName(const string& v)
{
    VarName = v;
    UpdateStatementText();
}

void Read::Draw(Output* pOut) const
{
    pOut->DrawReadAndWrite(LeftCorner, UI.READ_WDTH, UI.READ_HI, Text, Selected);
}

void Read::UpdateStatementText()
{
    ostringstream T;
    T << "read " << VarName;
    Text = T.str();
}
Point Read::GetOutletPoint(int branch) const
{

    // Rectangle - outlet at bottom center
    return Point(LeftCorner.x + UI.READ_WDTH / 2,
        LeftCorner.y + UI.READ_HI);
}

Point Read::GetInletPoint() const
{
    // Rectangle - inlet at top center
    return Point(LeftCorner.x + UI.READ_WDTH / 2,
        LeftCorner.y);
}

int Read::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool Read::IsPointInside(Point p) const
{
    return (p.x >= LeftCorner.x &&
        p.x <= LeftCorner.x + UI.READ_WDTH &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.READ_HI);
}

void Read::Edit(Input* pIn, Output* pOut)
{
    pOut->PrintMessage("Editing Read Statement: Enter variable name: ");
    string varName = pIn->GetString(pOut);
    if (!varName.empty())
    {
        setVarName(varName);
        pOut->PrintMessage("Read statement updated.");
    }
    else
    {
        pOut->PrintMessage("Edit cancelled. Variable name cannot be empty.");
	}
}

Statement* Read::Clone() const
{
    Read* newRead = new Read(*this);
    newRead->pOutConn = nullptr; // Reset outgoing connector for the cloned statement
	return newRead;
}

void Read::Save(ofstream& OutFile) const
{
    OutFile << "READ\t" << ID << "\t" << Center.x << "\t"
        << Center.y << "\t" << VarName << "\n";
}

void Read::Load(ifstream& InFile)
{
    int x, y;
    InFile >> ID >> Center.x >> Center.y >> VarName;
    
}


