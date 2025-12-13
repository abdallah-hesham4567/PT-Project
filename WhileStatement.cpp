#include "WhileStatement.h"
#include "..\GUI\Output.h"
#include <sstream>
#include "ApplicationManager.h"
using namespace std;


WhileStatement::WhileStatement(Point Lcorner, const string& cond)
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
    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI/2;

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
    return Inlet.x; // Top point of diamond
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
    // Convert ENUM to STRING
    string comparisonStr;
    if (Comp == EQUAL)
        comparisonStr = "EQL";
    else if (Comp == NOT_EQUAL)
        comparisonStr = "NOTEQL";
    else if (Comp == GREATER)
        comparisonStr = "GRT";
    else if (Comp == LESS)
        comparisonStr = "LSS";
    else if (Comp == GREATER_OR_EQUAL)
        comparisonStr = "GRTEQL";
    else if (Comp == LESS_OR_EQUAL)
        comparisonStr = "LSSEQL";

    OutFile << "COND\t" << ID << "\t"
        << Center.x << "\t" << Center.y << "\t"
        << LHS << "\t" << comparisonStr << "\t" << RHS;
}


void WhileStatement::Load(ifstream& InFile)
{
    string comparisonStr;
    InFile >> ID >> Center.x >> Center.y
        >> LHS >> comparisonStr >> RHS;

    // Convert STRING to ENUM
    if (comparisonStr == "EQL")
        Comp = EQUAL;
    else if (comparisonStr == "NOTEQL")
        Comp = NOT_EQUAL;
    else if (comparisonStr == "GRT")
        Comp = GREATER;
    else if (comparisonStr == "LSS")
        Comp = LESS;
    else if (comparisonStr == "GRTEQL")
        Comp = GREATER_OR_EQUAL;
    else if (comparisonStr == "LSSEQL")
        Comp = LESS_OR_EQUAL; 


    
}


string WhileStatement::getStatementType() const
{
    return "COND";
}

