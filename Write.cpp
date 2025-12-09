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

Point Write::GetOutletPoint(int branch) const
{
    // Rectangle - outlet at bottom center
    return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
        LeftCorner.y + UI.ASSGN_HI);
}

Point Write::GetInletPoint() const
{
    // Rectangle - inlet at top center
    return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
        LeftCorner.y);
}

int Write::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool Write::IsPointInside(Point p) const
{
    return (p.x >= LeftCorner.x &&
        p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.ASSGN_HI);
}