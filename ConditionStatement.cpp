#include "ConditionStatement.h"
#include "..\GUI\Output.h"
#include <sstream>
#include "ApplicationManager.h"
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
    Center.x = LeftCorner.x + UI.COND_WDTH / 2;
    Center.y = LeftCorner.y + UI.COND_HI/2;
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

void ConditionStatement::Edit()
{
    ApplicationManager* pManager;
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Editing Condition Statement: Enter the LHS:");
	string LHS = pIn->GetVariableOrVal(pOut);  
	pOut->PrintMessage("Enter the comparison operator (==, !=, <, <=, >, >=):");
	string op = pIn->GetCompOperator(pOut);
    pOut->PrintMessage("Enter the RHS:");
    string RHS = pIn->GetVariableOrVal(pOut);      
    string ConditionText = LHS + " " + op + " " + RHS;
    Condition = ConditionText;
	pOut->ClearStatusBar();
    

}
//void ConditionStatement::SetBranchConnector(Connector* pConn, int branch)
//{
//    if (branch == 1)      // True branch
//        TrueBranch = pConn;
//    else if (branch == 2) // False branch
//        FalseBranch = pConn;
//}

Statement* ConditionStatement::Clone() const
{
    return nullptr;
}


Point ConditionStatement::GetOutletPoint(int branch) const
{
    // Diamond shape - upper point is LeftCorner
    

    if (branch == 1) // YES - right side
        return Point(Center.x + UI.COND_WDTH / 2, Center.y);
    else if (branch == 2) // NO - left side
        return Point(Center.x - UI.COND_WDTH / 2, Center.y);
    else // Default - bottom
        return Point(Center.x, Center.y + UI.COND_HI / 2);
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
    return 2; // YES and NO branches
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
        << LHS << "\t" << comparisonStr << "\t"<<RHS;

}


void ConditionStatement::Load(ifstream& InFile)
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




string ConditionStatement::getStatementType() const
{
    return "COND";
}


