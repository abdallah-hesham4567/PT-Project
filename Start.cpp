#include "Start.h"
#include "..\GUI\Output.h"
#include "ApplicationManager.h"
Start::Start(Point C)
{
    Center = C;
    pOutConn = NULL;

    // set inlet (top) and outlet (bottom) of the oval
    Inlet.x = Center.x;
    Inlet.y = Center.y - UI.START_END_HI / 2;

    Outlet.x = Center.x;
    Outlet.y = Center.y + UI.START_END_HI / 2;

    UpdateStatementText();
}

void Start::UpdateStatementText()
{
    Text = "Start";
}

void Start::Draw(Output* pOut) const
{
    // DrawStart expects center point, width, height, text, selected
    pOut->DrawStart(Center, UI.START_END_WDTH, UI.START_END_HI, Text, Selected);
}

void Start::Edit()
{
    ApplicationManager* pManager;
	// Start statement has no editable parameters
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Start statement has no editable parameters.");
}

Statement* Start::Clone() const
{
    //Start Statement cannot be cloned
    ApplicationManager* pManager;
    Output* pOut = pManager->GetOutput();
    pOut->PrintMessage("Start statement cannot be cloned.");
    return nullptr;
}


Point Start::GetOutletPoint(int branch) const
{
    return Point(Center.x,
        Outlet.y);
}

Point Start::GetInletPoint() const
{
    return Point(Inlet.x,
        Inlet.y);
}

int Start::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool Start::IsPointInside(Point p) const
{
    return (p.x >= Center.x - UI.START_END_HI / 2 &&
        p.x <= Center.x + UI.START_END_HI / 2 &&
        p.y >= Center.y - UI.START_END_HI / 2 &&
        p.y <= Center.y + UI.START_END_HI / 2);
}

void Start::Save(ofstream& OutFile) const
{
    OutFile << "STRT\t" << ID << "\t" << Center.x << "\t"
        << Center.y << "\n";
}

void Start::Load(ifstream& InFile)
{
    
    InFile >> ID >> Center.x >> Center.y;
    
}