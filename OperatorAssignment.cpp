#include "OperatorAssignment.h"
#include <sstream>


OperatorAssignment::OperatorAssignment(Point Lcorner, string LeftHS, char Oper, string R1, string R2)

{
	LHS = LeftHS;
	RHS1 = R1;
	Op = Oper;
	RHS2 = R2;
	


    UpdateStatementText();
    LeftCorner = Lcorner;
    pOutConn = NULL;

    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
	Center.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Center.y = LeftCorner.y + UI.ASSGN_HI / 2;
}

void OperatorAssignment::SetPosition(Point p)
{
    LeftCorner.x = p.x - UI.ASSGN_WDTH / 2;
    LeftCorner.y = p.y;

    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;
    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
    Center.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Center.y = LeftCorner.y + UI.ASSGN_HI / 2;
}


void OperatorAssignment::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}
void OperatorAssignment::setRHS1(string R)
{
    RHS1 = R;
    UpdateStatementText();
}
void OperatorAssignment::setOp(char O)
{
    Op = O;
    UpdateStatementText();
}
void OperatorAssignment::setRHS2(string R)
{
    RHS2 = R;
	UpdateStatementText();
}

void OperatorAssignment::Draw(Output* pOut) const
{
    pOut->DrawAssignAndDeclare(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
}

void OperatorAssignment::Edit(Input* pIn, Output* pOut)
{
    pOut->PrintMessage("Enter new LHS variable name:");
    string newLHS = pIn->GetVariable(pOut);
    setLHS(newLHS);
    pOut->PrintMessage("Enter new first operand (RHS1):");
    string newRHS1 = pIn->GetVariableOrVal(pOut);
    setRHS1(newRHS1);
    pOut->PrintMessage("Enter new operator (+, -, *, /):");
    char newOp = pIn->GetArithOperator(pOut);
    setOp(newOp);
    pOut->PrintMessage("Enter new second operand (RHS2):");
    string newRHS2 = pIn->GetVariableOrVal(pOut);
    setRHS2(newRHS2);
	pOut->ClearStatusBar();
}

Statement* OperatorAssignment::Clone() const
{
    OperatorAssignment* newOppAssign = new OperatorAssignment(*this);
    newOppAssign->SetOutConn(nullptr);
    return newOppAssign;
}

void OperatorAssignment::UpdateStatementText()
{
    ostringstream T;
    T << LHS << " = " << RHS1 << " " << Op << " " << RHS2;
	Text = T.str();
}

Point OperatorAssignment::GetOutletPoint(int branch) const
{
    // Rectangle - outlet at bottom center
    return Point(Outlet.x,
        Outlet.y);
}

Point OperatorAssignment::GetInletPoint() const
{
    /// Rectangle - inlet at bottom center
    return Point(Inlet.x,
        Inlet.y);
}

int OperatorAssignment::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool OperatorAssignment::IsPointInside(Point p) const
{
    return (p.x >= LeftCorner.x &&
        p.x <= LeftCorner.x + UI.ASSGN_WDTH &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.ASSGN_HI);
}


void OperatorAssignment::Save(ofstream& OutFile) const
{
    // Convert ENUM to STRING
    string operatorStr;
    if (Opp == ADD_OP)
        operatorStr = "ADD";
    else if (Opp == SUB_OP)
        operatorStr = "SUB";
    else if (Opp == MUL_OP)
        operatorStr = "MUL";
    else if (Opp == DIV_OP)
        operatorStr = "DIV";

    OutFile << "OP_ASSIGN\t" << ID << "\t"
        << Center.x << "\t" << Center.y << "\t"
        << LHS << "\t" << RHS1 << "\t" << operatorStr << "\t"<<RHS2;

   
}


void OperatorAssignment::Load(ifstream& InFile)
{
    string operatorStr;
    InFile >> ID >> Center.x >> Center.y
        >> LHS >> RHS1 >> operatorStr >> RHS2;

    // Convert STRING to ENUM
    if (operatorStr == "ADD")
        Opp = ADD_OP;
    else if (operatorStr == "SUB")
        Opp = SUB_OP;
    else if (operatorStr == "MUL")
        Opp = MUL_OP;
    else if (operatorStr == "DIV")
        Opp = DIV_OP;

   
}















//
//bool OperatorAssignment::ValidateRHS(string RHS)
//{
//    // Remove spaces
//    RHS.erase(remove_if(RHS.begin(), RHS.end(), ::isspace), RHS.end());
//
//    // Count operators
//    int opCount = 0;
//    char op = 0;
//    int opPos = -1;
//
//    for (int i = 0; i < RHS.size(); i++)
//    {
//		if (RHS[i] == '+' || RHS[i] == '-' || RHS[i] == '*' || RHS[i] == '/')  
//        {
//            opCount++;
//            op = RHS[i];
//            opPos = i;
//        }
//    }
//
//    // Case 1: No operator → must be variable or value
//    if (opCount == 0)
//        return IsVariable(RHS) || IsValue(RHS);
//
//    // Case 2: More than 1 operator → invalid
//    if (opCount > 1)
//        return false;
//
//    // Case 3: Exactly one operator
//    string left = RHS.substr(0, opPos);
//    string right = RHS.substr(opPos + 1);
//
//    if (left.empty() || right.empty())
//        return false;
//
//    return (IsVariable(left) || IsValue(left)) &&
//        (IsVariable(right) || IsValue(right));
//}
//
