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

    Inlet.x = LeftCorner.x + UI.IO_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.IO_HI;

    UpdateStatementText();
}

void Read::setVarName(const string& v)
{
    VarName = v;
    UpdateStatementText();
}

void Read::Draw(Output* pOut) const
{
    pOut->DrawInputOutput(LeftCorner, UI.IO_WDTH, UI.IO_HI, Text, Selected);
}

void Read::UpdateStatementText()
{
    ostringstream T;
    T << "read " << VarName;
    Text = T.str();
}