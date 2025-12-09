#include "Start.h"
#include "..\GUI\Output.h"

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