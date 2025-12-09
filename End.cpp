#include "End.h"
#include "..\GUI\Output.h"

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