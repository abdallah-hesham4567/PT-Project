#include "Start.h"
#include "..\GUI\Output.h"

Start::Start(Point C)
{
    Center = C;
    pOutConn = NULL;

    // set inlet (top) and outlet (bottom) of the oval
    Inlet.x = Center.x;
    Inlet.y = Center.y - UI.START_END_HI / 2;

    Outlet.x = Center.x;
    Outlet.y = Center.y + UI.START_END_HI / 2;

    UpdateStatementText();
}

void Start::UpdateStatementText()
{
    Text = "Start";
}

void Start::Draw(Output* pOut) const
{
    // DrawStart expects center point, width, height, text, selected
    pOut->DrawStart(Center, UI.START_END_WDTH, UI.START_END_HI, Text, Selected);
}


Point Start::GetOutletPoint(int branch) const
{
    // Rectangle - outlet at bottom center
    return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
        LeftCorner.y + UI.ASSGN_HI);
}

Point Start::GetInletPoint() const
{
    // Rectangle - inlet at top center
    return Point(LeftCorner.x + UI.ASSGN_WDTH / 2,
        LeftCorner.y);
}

int Start::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool Start::IsPointInside(Point p) const
{
    return (p.x >= LeftCorner.x &&
        p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.ASSGN_HI);
}