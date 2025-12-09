#include "ConditionStatement.h"
#include "..\GUI\Output.h"
#include <sstream>

ConditionStatement::ConditionStatement(Point Lcorner, const string& cond)
{
    LeftCorner = Lcorner;
    Condition = cond;
    TrueBranch = nullptr;
    FalseBranch = nullptr;

    Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    Inlet.y = LeftCorner.y;

    OutletTrue.x = LeftCorner.x;
    OutletTrue.y = LeftCorner.y + UI.COND_HI;

    OutletFalse.x = LeftCorner.x + UI.COND_WDTH;
    OutletFalse.y = LeftCorner.y + UI.COND_HI;

    UpdateStatementText();
}


void ConditionStatement::setCondition(const string& cond)
{
    Condition = cond;
    UpdateStatementText();
}

void ConditionStatement::UpdateStatementText()
{
    ostringstream T;
    T << "if (" << Condition << ")";
    Text = T.str();
}


void ConditionStatement::Draw(Output* pOut) const
{
    pOut->DrawConditionalStat(LeftCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected);
}


Point ConditionalStatement::GetOutletPoint(int branch) const
{
    // Diamond shape - upper point is LeftCorner
    Point center;
    center.x = LeftCorner.x;
    center.y = LeftCorner.y + UI.COND_HI / 2;

    if (branch == 1) // YES - right side
        return Point(center.x + UI.COND_WDTH / 2, center.y);
    else if (branch == 2) // NO - left side
        return Point(center.x - UI.COND_WDTH / 2, center.y);
    else // Default - bottom
        return Point(center.x, center.y + UI.COND_HI / 2);
}

Point ConditionalStatement::GetInletPoint() const
{
    return LeftCorner; // Top point of diamond
}

int ConditionalStatement::GetExpectedOutConnCount() const
{
    return 2; // YES and NO branches
}

bool ConditionalStatement::IsConditional() const
{
    return true;
}

bool ConditionalStatement::IsPointInside(Point p) const
{
    // Check if point is inside diamond shape
    Point center;
    center.x = LeftCorner.x;
    center.y = LeftCorner.y + UI.COND_HI / 2;

    // Simple bounding box check (you can make it more precise)
    return (p.x >= center.x - UI.COND_WDTH / 2 &&
        p.x <= center.x + UI.COND_WDTH / 2 &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.COND_HI);
}



