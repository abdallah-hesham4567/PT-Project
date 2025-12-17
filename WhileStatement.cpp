#include "WhileStatement.h"
#include "..\GUI\Output.h"
#include <sstream>
#include "ApplicationManager.h"
using namespace std;


WhileStatement::WhileStatement(Point Lcorner, const string& LHS, const string& OP, const string& RHS)
{

    LeftCorner = Lcorner;
    Condition = LHS + OP + RHS;
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
    Center.y = LeftCorner.y + UI.COND_HI / 2;
    UpdateStatementText();
}

void WhileStatement::SetPosition(Point p)
{
    // Center the diamond around the clicked point
    LeftCorner.x = p.x - UI.COND_WDTH / 2;
    LeftCorner.y = p.y;

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

Point WhileStatement::GetPosition() const
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
    this->setCondition(newCondition);
	pOut->ClearStatusBar();
}

Statement* WhileStatement::Clone() const
{
    WhileStatement* newWhile = new WhileStatement(*this);
	//while has two outgoing connectors, reset them for the cloned statement
    newWhile->setTrueBranch(nullptr);
	newWhile->setFalseBranch(nullptr);
	return newWhile;

}


Point WhileStatement::GetOutletPoint(int branch) const
{
    if (branch == 1) // YES - right side
        return Point(Center.x + UI.COND_WDTH / 2, Center.y);
    else if (branch == 2) // NO - left side
        return Point(Center.x - UI.COND_WDTH / 2, Center.y);
    else // Default - bottom
        return Point(Center.x, Center.y + UI.COND_HI / 2);
}

Point WhileStatement::GetInletPoint() const
{
    Point inlet;
    inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
    inlet.y = LeftCorner.y;
    return inlet; // Top point of diamond
}

int WhileStatement::GetExpectedOutConnCount() const
{
    return 2; // YES and NO branches
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
    // Diamond equation: dx/halfW + dy/halfH <= 1
    return ((dx * halfH + dy * halfW) <= (halfW * halfH));
}

void WhileStatement::Save(ofstream& OutFile) const
{
    string comparisonStr = OpToString(op); // Use the helper function

    OutFile << "WHILE\t" << ID << "\t"
        << Inlet.x << "\t" << Inlet.y << "\t"
        << LHS << "\t" << comparisonStr << "\t" << RHS<<endl;
}

void WhileStatement::Load(ifstream& InFile)
{
    
    string opStr;
    InFile >> ID >> Inlet.x >> Inlet.y >> LHS >> opStr >> RHS;


    // Convert string back to operator
    if (opStr == "EQL")
        op = "==";
    else if (opStr == "NOTEQL")
        op = "!=";
    else if (opStr == "GRT")
        op = ">";
    else if (opStr == "LSS")
        op = "<";
    else if (opStr == "GRTEQL")
        op = ">=";
    else if (opStr == "LSSEQL")
        op = "<=";

    LeftCorner.x = Inlet.x - UI.COND_WDTH / 2;
    LeftCorner.y = Inlet.y;
   

    OutletTrue.x = LeftCorner.x;
    OutletTrue.y = LeftCorner.y + UI.COND_HI;

    OutletFalse.x = LeftCorner.x + UI.COND_WDTH;
    OutletFalse.y = LeftCorner.y + UI.COND_HI;
    
    Condition = LHS + op + RHS;
    UpdateStatementText();
}


string WhileStatement::getStatementType() const
{
    return "WHILE";
}

