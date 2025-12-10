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

    Point center;
    center.x = LeftCorner.x + UI.COND_WDTH / 2;
    center.y = LeftCorner.y + UI.COND_HI;

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

void ConditionStatement::Edit(ApplicationManager* pManager)
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Editing Condition Statement: Enter the LHS:");
	string LHS = pIn->GetVariableOrVal(pOut);  
	pOut->PrintMessage("Enter the comparison operator (==, !=, <, <=, >, >=):");
	string op = pIn->GetCompOperator(pOut);
    pOut->PrintMessage("Enter the RHS:");
    string RHS = pIn->GetVariableOrVal(pOut);      
    string ConditionText = LHS + " " + op + " " + RHS;
    setCondition(ConditionText);
	pOut->ClearStatusBar();
    

}
void ConditionStatement::SetBranchConnector(Connector* pConn, int branch)
{
    if (branch == 1)      // True branch
        TrueBranch = pConn;
    else if (branch == 2) // False branch
        FalseBranch = pConn;
}

Statement* ConditionStatement::Clone() const
{
	return new ConditionStatement(*this);
}


Point ConditionStatement::GetOutletPoint(int branch) const
{
    // Diamond shape - upper point is LeftCorner
    Point center;
    center.x = LeftCorner.x + UI.COND_WDTH /2;
    center.y = LeftCorner.y + UI.COND_HI / 2;

    if (branch == 1) // YES - right side
        return Point(center.x + UI.COND_WDTH / 2, center.y);
    else if (branch == 2) // NO - left side
        return Point(center.x - UI.COND_WDTH / 2, center.y);
    else // Default - bottom
        return Point(center.x, center.y + UI.COND_HI / 2);
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
    // Check if point is inside diamond shape
    Point center;
    center.x = LeftCorner.x + UI.COND_WDTH /2;
    center.y = LeftCorner.y + UI.COND_HI / 2;

    float dx = abs(p.x - center.x);
    float dy = abs(p.y - center.y);

    int halfW = UI.COND_WDTH / 2;
    int halfH = UI.COND_HI / 2;
    // Diamond equation: dx/halfW + dy/halfH <= 1
    return ((dx * halfH + dy * halfW) <= (halfW * halfH));
}

void ConditionStatement::Save(ofstream& OutFile) const
{
    OutFile << "COND\t" << ID << "\t" << LeftCorner.x << "\t"
        << LeftCorner.y << "\t" << Condition << "\n";
}

void ConditionStatement::Load(ifstream& InFile)
{
    int x, y , trueID = -1, falseID = -1;;
    InFile >> ID >> x >> y >> trueID >> falseID;
	InFile.ignore(); // Ignore tab
	getline(InFile, Condition);
	LeftCorner.x = x;
	LeftCorner.y = y;
	// Set position of the output connector
   
    TrueBranch = trueID;
    FalseBranch = falseID;

}


