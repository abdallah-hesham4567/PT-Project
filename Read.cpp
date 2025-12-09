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

    UpdateStatementText();
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

void Read::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Enter new variable name: ");
    string newVar = pIn->GetString(pOut);

    VarName = newVar;   // Update internal variable

    UpdateStatementText();   // regenerate text
}
