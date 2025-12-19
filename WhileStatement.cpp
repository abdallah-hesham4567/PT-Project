#include "WhileStatement.h"
#include "..\GUI\Output.h"
#include <sstream>
#include "ApplicationManager.h"
using namespace std;


WhileStatement::WhileStatement(Point Lcorner, const string& LHS, const string& OP, const string& RHS)
{
    LeftCorner = Lcorner;
    
    TrueBranch = nullptr;
    FalseBranch = nullptr;
    this->RHS = RHS;
    this->LHS = LHS;
    op = OP;
    Condition = LHS + " " + op + " " + RHS;
    Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    Inlet.y = LeftCorner.y;

    OutletTrue.x = LeftCorner.x + UI.COND_WDTH;
    OutletTrue.y = LeftCorner.y + UI.COND_HI /2;

    OutletFalse.x = LeftCorner.x ;
    OutletFalse.y = LeftCorner.y + UI.COND_HI /2;

    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI / 2;

    UpdateStatementText();
}

void WhileStatement::SetPosition(Point p)
{
    // Center the diamond around the clicked point
    LeftCorner.x = p.x - UI.COND_WDTH / 2;
    LeftCorner.y = p.y- UI.COND_HI/2 ;

    // Recalculate all dependent points
    Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    Inlet.y = LeftCorner.y;

    OutletTrue.x = LeftCorner.x + UI.COND_WDTH;
    OutletTrue.y = LeftCorner.y + UI.COND_HI / 2;

    OutletFalse.x = LeftCorner.x;
    OutletFalse.y = LeftCorner.y + UI.COND_HI / 2;

    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI / 2;
}

Point WhileStatement::GetPosition() const              //Getters
{
	return LeftCorner;
}

int WhileStatement::GetWidth() const
{
    return UI.COND_WDTH;
}

int WhileStatement::GetHeight() const
{
    return UI.COND_HI;
}

bool WhileStatement::Evaluate(Variable vars[], int varCount)       // Used in run
{
    double v1, v2;

    // LHS
    if (IsValue(LHS))
        v1 = stod(LHS);
    else
        for (int i = 0; i < varCount; i++)
            if (vars[i].name == LHS)
                v1 = vars[i].value;

    // RHS
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
string WhileStatement::GetLHS() const
{
    return LHS;
}
string WhileStatement::GetRHS() const
{
    return RHS;
}
void WhileStatement::setCondition(const string& cond)       
{
    Condition = cond;
    UpdateStatementText();
}

void WhileStatement::UpdateStatementText()
{
    ostringstream T;
    T << "while (" << Condition << ")";
    Text = T.str();
}

void WhileStatement::Draw(Output* pOut) const
{

    pOut->DrawConditionalStat(LeftCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected);

}

void WhileStatement::Edit(Input* pIn, Output* pOut)
{
    pOut->PrintMessage("Edit While Statement Condition: Enter new LHS:");
    string LHS = pIn->GetVariableOrVal(pOut);

    pOut->PrintMessage("Enter new comparison operator (==, !=, <, <=, >, >=):");
    string op = pIn->GetCompOperator(pOut);

    pOut->PrintMessage("Enter new RHS:");
    string RHS = pIn->GetVariableOrVal(pOut);

    string newCondition = LHS + " " + op + " " + RHS;
    this->LHS = LHS;
    this->op = op;
    this->RHS = RHS;
    this->setCondition(newCondition);
	pOut->ClearStatusBar();

}

Statement* WhileStatement::Clone() const
{
    WhileStatement* newWhile = new WhileStatement(*this);
	//while has two outgoing connectors, reset them for the cloned statement
    newWhile->setTrueBranch(nullptr);
	newWhile->setFalseBranch(nullptr);
    newWhile->SetSelected(false);
	return newWhile;

}


Point WhileStatement::GetOutletPoint(int branch) const
{
    if (branch == 1)                             // YES - right side
        return OutletTrue;
    else if (branch == 2)                       // NO - left side
        return OutletFalse;
    
}

Point WhileStatement::GetInletPoint() const
{
    return Inlet;                         // Top point of diamond
}

int WhileStatement::GetExpectedOutConnCount() const
{
    return 2;                            // YES and NO branches
}

bool WhileStatement::IsConditional() const
{
    return true;
}

bool WhileStatement::IsPointInside(Point p) const
{
    float dx = abs(p.x - Center.x);
    float dy = abs(p.y - Center.y);

    int halfW = UI.COND_WDTH / 2;
    int halfH = UI.COND_HI / 2;
                                           
    return ((dx * halfH + dy * halfW) <= (halfW * halfH)); // Diamond equation: dx/halfW + dy/halfH <= 1
}

void WhileStatement::Save(ofstream& OutFile) const
{
    string comparisonStr = OpToString(op);                 // Use the helper function

    OutFile << "WHILE\t" << ID << "\t"
        << Inlet.x << "\t" << Inlet.y << "\t"
        << LHS << "\t" << comparisonStr << "\t" << RHS<<endl;
}

void WhileStatement::Load(ifstream& InFile)
{
    
    string opStr;
    InFile >> ID >> Inlet.x >> Inlet.y >> LHS >> opStr >> RHS;

    op = StringToOp(opStr);               //helper function we did

    LeftCorner.x = Inlet.x - UI.COND_WDTH / 2;
    LeftCorner.y = Inlet.y;
   

    OutletTrue.x = LeftCorner.x + UI.COND_WDTH;
    OutletTrue.y = LeftCorner.y + UI.COND_HI /2;

    OutletFalse.x = LeftCorner.x  ;
    OutletFalse.y = LeftCorner.y + UI.COND_HI /2;

    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI / 2;

    Condition = LHS + op + RHS;
    UpdateStatementText();

}




