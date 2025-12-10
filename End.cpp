#include "End.h"
#include "..\GUI\Output.h"
#include "..\ApplicationManager.h"
End::End(Point C)
{
    Center = C;
    pInConn = NULL;

    // inlet is top of the oval (where connection will arrive)
    Inlet.x = Center.x;
    Inlet.y = Center.y - UI.START_END_HI / 2;

    Outlet.x = Center.x;
    Outlet.y = Center.y + UI.START_END_HI / 2;

    UpdateStatementText();
}

void End::UpdateStatementText()
{
    Text = "End";
}

void End::Draw(Output* pOut) const
{
    pOut->DrawEnd(Center, UI.START_END_WDTH, UI.START_END_HI, Text, Selected);
}

Point End::GetOutletPoint(int branch) const
{
    
    return Point(Center.x,
        Outlet.y);
}

Point End::GetInletPoint() const
{
  
    return Point(Inlet.x,
        Inlet.y);
}

int End::GetExpectedOutConnCount() const
{
    return 1; // Normal statement has 1 output
}

bool End::IsPointInside(Point p) const
{
    return (p.x >= Center.x - UI.START_END_HI / 2 &&
        p.x <= Center.x + UI.START_END_HI / 2 &&
        p.y >= Center.y - UI.START_END_HI / 2 &&
        p.y <= Center.y + UI.START_END_HI / 2);
}

void End::Edit()
{
    ApplicationManager* pManager;
	// No editable parameters 
    Output* pOut;
	pOut->PrintMessage("End statement has no editable parameters.");

}

Statement* End::Clone() const
{
	//End statement cannot be cloned
    ApplicationManager* pManager;
    Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("End statement cannot be cloned.");
    return nullptr;
}

void End::Save(ofstream& OutFile) const
{
    OutFile << "END\t" << ID << "\t" << Center.x << "\t"
        << Center.y  << "\n";
}

void End::Load(ifstream& InFile)
{
    int x, y;
    InFile >> ID >> Center.x >> Center.y;
    
}

