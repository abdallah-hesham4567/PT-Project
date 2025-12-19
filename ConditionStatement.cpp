#include "ConditionStatement.h"
#include "..\GUI\Output.h"
#include <sstream>
#include "ApplicationManager.h"
ConditionStatement::ConditionStatement(Point Lcorner, const string& LHS, const string& OP, const string& RHS)
{
    LeftCorner = Lcorner;
    Condition = LHS + OP +RHS;
    TrueBranch = nullptr;
    FalseBranch = nullptr;
    this->RHS = RHS;
    this->LHS = LHS;
    op = OP;
    

    Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    Inlet.y = LeftCorner.y;

    OutletTrue.x = LeftCorner.x;
    OutletTrue.y = LeftCorner.y + UI.COND_HI;

    OutletFalse.x = LeftCorner.x + UI.COND_WDTH;
    OutletFalse.y = LeftCorner.y + UI.COND_HI;
    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI/2;
    UpdateStatementText();
}


void ConditionStatement::SetPosition(Point p)
{
    // Center the diamond around the clicked point
    LeftCorner.x = p.x - UI.COND_WDTH / 2;
    LeftCorner.y = p.y- UI.COND_HI /2 ;

    // Recalculate all dependent points
    Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    Inlet.y = LeftCorner.y;

    OutletTrue.x = LeftCorner.x;
    OutletTrue.y = LeftCorner.y + UI.COND_HI;

    OutletFalse.x = LeftCorner.x + UI.COND_WDTH;
    OutletFalse.y = LeftCorner.y + UI.COND_HI;

    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI / 2;
}

Point ConditionStatement::GetPosition() const
{
	return LeftCorner;
}

int ConditionStatement::GetWidth() const
{
	return UI.COND_WDTH;
}

int ConditionStatement::GetHeight() const
{  
	return UI.COND_HI;
}

bool ConditionStatement::Evaluate(Variable vars[], int varCount)
{
    double v1, v2;

    // operand 1
    if (IsValue(LHS))
        v1 = stod(LHS);
    else
        for (int i = 0; i < varCount; i++)
            if (vars[i].name == LHS)
                v1 = vars[i].value;

    // operand 2
    if (IsValue(RHS))
        v2 = stod(RHS);
    else
        for (int i = 0; i < varCount; i++)
            if (vars[i].name == RHS)
                v2 = vars[i].value;

    if (op == ">")  return v1 > v2;
    if (op == "<")  return v1 < v2;
    if (op == "==") return v1 == v2;
    if (op == "!=") return v1 != v2;
    if (op == ">=") return v1 >= v2;
    return v1 <= v2;
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




Statement* ConditionStatement::Clone() const
{
    ConditionStatement* newCond = new ConditionStatement(*this);
    //while has two outgoing connectors, reset them for the cloned statement
    newCond->setTrueBranch(nullptr);
    newCond->setFalseBranch(nullptr);
    newCond->SetSelected(false);
    return newCond;
}


Point ConditionStatement::GetOutletPoint(int branch) const
{
    
    if (branch == 1) // YES - right side
        return Point(Center.x + UI.COND_WDTH / 2, Center.y);
    else if (branch == 2) // NO - left side
        return Point(Center.x - UI.COND_WDTH / 2, Center.y);
}

Point ConditionStatement::GetInletPoint() const
{
    Point inlet;
    inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    inlet.y = LeftCorner.y;
    return inlet; // Top point of diamond
}

int ConditionStatement::GetExpectedOutConnCount() const
{
    return 2;                                  // YES and NO branches
}

bool ConditionStatement::IsConditional() const
{
    return true;
}

bool ConditionStatement::IsPointInside(Point p) const
{
   

    float dx = abs(p.x - Center.x);
    float dy = abs(p.y - Center.y);

    int halfW = UI.COND_WDTH / 2;
    int halfH = UI.COND_HI / 2;
    // Diamond equation: dx/halfW + dy/halfH <= 1
    return ((dx * halfH + dy * halfW) <= (halfW * halfH));
}

void ConditionStatement::Save(ofstream& OutFile) const
{
    string comparisonStr = OpToString(op); // Use the helper function
    OutFile << "COND\t" << ID << "\t"
        << Inlet.x << "\t" << Inlet.y << "\t"
        << LHS << "\t" << comparisonStr << "\t" << RHS << endl;
}


void ConditionStatement::Load(ifstream& InFile)
{
    string opStr;
    InFile >> ID >> Inlet.x >> Inlet.y >> LHS >> opStr >> RHS;


     op = StringToOp(opStr);               //helper function we did

    LeftCorner.x = Inlet.x - UI.COND_WDTH / 2;
    LeftCorner.y = Inlet.y;

    OutletTrue.x = LeftCorner.x;
    OutletTrue.y = LeftCorner.y + UI.COND_HI;

    OutletFalse.x = LeftCorner.x + UI.COND_WDTH;
    OutletFalse.y = LeftCorner.y + UI.COND_HI;

    Condition = LHS + op + RHS;

    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI / 2;

    UpdateStatementText();
}




string ConditionStatement::getStatementType() const
{
    return "COND";
}

void ConditionStatement::Edit(Input* pIn, Output* pOut)
{ // enter lhs , op and rhs
    string LHS = pIn->GetVariableOrVal(pOut);

    pOut->PrintMessage("Enter the comparison operator (==, !=, <, <=, >, >=):");
    string op = pIn->GetCompOperator(pOut);

    pOut->PrintMessage("Enter the RHS:");
    string RHS = pIn->GetVariableOrVal(pOut);

    string ConditionText = LHS + " " + op + " " + RHS;
    this->LHS = LHS;
    this->op = op;
    this->RHS = RHS;
    Condition = ConditionText;
	this->setCondition(ConditionText);
    pOut->ClearStatusBar();


}


