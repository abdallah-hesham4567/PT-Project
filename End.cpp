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
    LCorner.x = Center.x - UI.START_END_WDTH / 2;
    LCorner.y = Center.y - UI.START_END_HI / 2;

    UpdateStatementText();
}

void End::UpdateStatementText()
{
    Text = "End";
}

void End::Draw(Output* pOut) const
{
    pOut->DrawEnd(LCorner, UI.START_END_WDTH, UI.START_END_HI, Text, Selected);
}

Point End::GetOutletPoint(int branch) const
{
    
    return Point(Outlet.x,
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
    return (p.x >= LCorner.x &&
        p.x <= LCorner.x + UI.START_END_WDTH &&
        p.y >= LCorner.y &&
        p.y <= LCorner.y + UI.START_END_HI);
}

void End::Edit(Input* pIn, Output* pOut)
{
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

Point End::GetPosition() const
{
	return LCorner;
}

int End::GetWidth() const
{
    return UI.START_END_WDTH;
}

int End::GetHeight() const
{
    return UI.START_END_HI;
}

void End::Save(ofstream& OutFile) const
{
    OutFile << "END\t" << ID << "\t" << Center.x << "\t"
        << Center.y  << "\n";
}

void End::Load(ifstream& InFile)
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

