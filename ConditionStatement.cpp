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


