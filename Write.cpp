#include "Write.h"
#include <sstream>
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h" 

using namespace std;

Write::Write(Point Lcorner, const string& expr)
{
    Expr = expr;
    LeftCorner = Lcorner;

    pOutConn = NULL;

    Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.READ_HI;

    UpdateStatementText();
}

void Write::setExpr(const string& e)
{
    Expr = e;
    UpdateStatementText();
}

void Write::Draw(Output* pOut) const
{
    pOut->DrawReadAndWrite(LeftCorner, UI.READ_WDTH, UI.READ_HI, Text, Selected);
}

void Write::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Edit Write - enter variable name or message:");
    string newContent = pIn->GetString(pOut);
    this->Text = newContent;
    UpdateStatementText();
    pOut->ClearStatusBar();
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
    return Point(LeftCorner.x + UI.READ_WDTH / 2,
        LeftCorner.y + UI.READ_HI);
}

Point Write::GetInletPoint() const
{
    // Rectangle - inlet at top center
    return Point(LeftCorner.x + UI.READ_WDTH / 2,
        LeftCorner.y);
}

int Write::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool Write::IsPointInside(Point p) const
{
    return (p.x >= LeftCorner.x &&
        p.x <= LeftCorner.x + UI.READ_WDTH &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.READ_HI);
}
