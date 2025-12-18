#include "Start.h"
#include "..\GUI\Output.h"
#include "ApplicationManager.h"
Start::Start(Point C)
{
    Center = C;
    pOutConn = NULL;

    
   LCorner.x = Center.x - UI.START_END_WDTH /2;
   LCorner.y = Center.y - UI.START_END_HI / 2;
    Inlet.x = Center.x;
    Inlet.y = Center.y - UI.START_END_HI / 2;
    Outlet.x = Center.x;
    Outlet.y = Center.y + UI.START_END_HI / 2;

    UpdateStatementText();
}

void Start::SetPosition(Point p)
{
    Center = p;
    pInConn = NULL;

    // inlet is top of the oval (where connection will arrive)
    Inlet.x = Center.x;
    Inlet.y = Center.y - UI.START_END_HI / 2;

    Outlet.x = Center.x;
    Outlet.y = Center.y + UI.START_END_HI / 2;
    LCorner.x = Center.x - UI.START_END_WDTH / 2;
    LCorner.y = Center.y - UI.START_END_HI / 2;

    UpdateStatementText();
}


void Start::UpdateStatementText()
{
    Text = "Start";
}

void Start::Draw(Output* pOut) const
{
    
    pOut->DrawStart(LCorner, UI.START_END_WDTH, UI.START_END_HI, Text, Selected);
}

void Start::Edit(Input* pIn, Output* pOut)
{
	// Start statement has no editable parameters
	pOut->PrintMessage("Start statement has no editable parameters.");
}

Statement* Start::Clone() const
{
    Start* newStart = new Start(*this);
    newStart->pOutConn = nullptr; // Reset outgoing connector for the cloned statement
    return newStart;
}

Point Start::GetPosition() const
{
	return LCorner;
}

int Start::GetWidth() const
{
	return UI.START_END_WDTH;
}

int Start::GetHeight() const
{
	return UI.START_END_HI;
}


Point Start::GetOutletPoint(int branch) const
{
    return Outlet;
}

Point Start::GetInletPoint() const
{
    return Inlet;
}

int Start::GetExpectedOutConnCount() const
{
    return 1;                                      // Normal statement has 1 output
}

bool Start::IsPointInside(Point p) const
{
    return (p.x >= LCorner.x &&
        p.x <= LCorner.x + UI.START_END_WDTH &&
        p.y >= LCorner.y &&
        p.y <= LCorner.y + UI.START_END_HI );
}


void Start::Save(ofstream& OutFile) const
{
    OutFile << "STRT\t" << ID << "\t" << Center.x << "\t"
        << Center.y << "\n";
}

void Start::Load(ifstream& InFile)
{
    int x, y;
    InFile >> ID >> x >> y;
    Center.x = x;
    Center.y = y;
    LCorner.x = Center.x - UI.START_END_WDTH / 2;
    LCorner.y = Center.y - UI.START_END_HI / 2;

    Inlet.x = Center.x;
    Inlet.y = Center.y - UI.START_END_HI / 2;

    Outlet.x = Center.x;
    Outlet.y = Center.y + UI.START_END_HI / 2;

    UpdateStatementText();
}



