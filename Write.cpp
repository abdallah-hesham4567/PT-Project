#include "Write.h"
#include <sstream>
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

using namespace std;

Write::Write(Point Lcorner, const string& expr)
{
    Expr = expr;
    LeftCorner = Lcorner;

    pOutConn = NULL;

    Inlet.x = LeftCorner.x + UI.IO_WDTH / 2;
    Inlet.y = Left::LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.IO_HI;

    UpdateStatementText();
}

void Write::setExpr(const string& e)
{
    Expr = e;
    UpdateStatementText();
}

void Write::Draw(Output* pOut) const
{
    pOut->DrawInputOutput(LeftCorner, UI.IO_WDTH, UI.IO_HI, Text, Selected);
}

void Write::UpdateStatementText()
{
    ostringstream T;
    T << "write " << Expr;
    Text = T.str();
}