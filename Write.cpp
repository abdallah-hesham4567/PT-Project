#include "Write.h"
#include <sstream>
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h" 

using namespace std;

Write::Write(Point Lcorner, const string& expr)      //Constructor
{
    Expr = expr;
    LeftCorner = Lcorner;

    pOutConn = NULL;

    Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.READ_HI;
    Center.x = LeftCorner.x + UI.READ_WDTH / 2;
    Center.y = LeftCorner.y + UI.READ_HI / 2;
    UpdateStatementText();
}

void Write::SetPosition(Point p)        //SetPosition for Clone 
{
    LeftCorner.x = p.x - UI.READ_WDTH / 2;
    LeftCorner.y = p.y;

    Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.READ_HI;

    Center.x = LeftCorner.x + UI.READ_WDTH / 2;
    Center.y = LeftCorner.y + UI.READ_HI / 2;
}

Point Write::GetPosition() const
{
	return LeftCorner;
}

int Write::GetWidth() const
{
	return UI.WRITE_WDTH;
}

int Write::GetHeight() const
{
    return UI.WRITE_HI;
}

void Write::Execute(Variable vars[], int& varCount, Input*, Output* pOut)
{
    for (int i = 0; i < varCount; i++)
    {
        if (vars[i].name == Expr)
        {
            ostringstream oss;
            oss << vars[i].value;  

            pOut->PrintOutput(oss.str());
            return;
        }
    }
    pOut->PrintOutput(Expr);
}




void Write::setExpr(const string& e)
{
    Expr = e;
    UpdateStatementText();
}

void Write::Draw(Output* pOut) const
{
    pOut->DrawReadAndWrite(LeftCorner, UI.READ_WDTH, UI.READ_HI, Text, Selected);
}

void Write::Edit(Input* pIn, Output* pOut)
{
    pOut->PrintMessage("Edit Write Statement: Enter new expression:");
    string newExpr = pIn->GetString(pOut);
    if (!newExpr.empty())
    {
        this->setExpr(newExpr);
        pOut->PrintMessage("Write statement updated.");
    }
    else
    {
        pOut->PrintMessage("Edit cancelled. Expression not changed.");
	}
}

Statement* Write::Clone() const
{
    Write* newWrite = new Write(*this);
	
    return newWrite;
}

void Write::UpdateStatementText()                        
{
    ostringstream T;
    T << "write " << Expr;
    Text = T.str();
}

Point Write::GetOutletPoint(int branch) const            //return outlet point for connector
{
   
    return Outlet;
}

Point Write::GetInletPoint() const                 // return inlet point for connector
{
    
    return Inlet;
}

int Write::GetExpectedOutConnCount() const
{
    return 1;                                         // Normal statement has 1 output
}

bool Write::IsPointInside(Point p) const
{
    return (p.x >= LeftCorner.x &&
        p.x <= LeftCorner.x + UI.READ_WDTH &&
        p.y >= LeftCorner.y &&
        p.y <= LeftCorner.y + UI.READ_HI);
}

void Write::Save(ofstream& OutFile) const 
{
    OutFile << "WRITE\t" << ID << "\t" << LeftCorner.x << "\t"
        << LeftCorner.y << "\t" << Expr << "\n";
}

void Write::Load(ifstream& InFile)
{

    InFile >> ID >> LeftCorner.x >> LeftCorner.y >> Expr;
    Inlet.x = LeftCorner.x + UI.READ_WDTH / 2;
    Inlet.y = LeftCorner.y;

    Outlet.x = Inlet.x;
    Outlet.y = LeftCorner.y + UI.READ_HI;
    Center.x = LeftCorner.x + UI.READ_WDTH / 2;
    Center.y = LeftCorner.y + UI.READ_HI / 2;
    UpdateStatementText();
}


