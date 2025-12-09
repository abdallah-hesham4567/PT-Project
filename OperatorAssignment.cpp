#include "OperatorAssignment.h"


OperatorAssignment::OperatorAssignment(Point Lcorner, string LeftHS, string Oper, string R1, string R2)
{
    LHS = LeftHS;
    Op = Oper;
    RHS1 = R1;
    RHS2 = R2;

    UpdateStatementText();

    LeftCorner = Lcorner;
    pOutConn = NULL;

    Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void OperatorAssignment::setLHS(const string& L)
{
    LHS = L;
    UpdateStatementText();
}

void OperatorAssignment::setOp(char O)
{
    Op = O;
    UpdateStatementText();
}

void OperatorAssignment::setRHS1(string R)
{
    RHS1 = R;
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


void OperatorAssignment::UpdateStatementText()
{
    ostringstream T;
    T << LHS << " = " <<RHS1<<" " << Op << " " << RHS2;
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
