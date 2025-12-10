#include "ActionSelect.h"

ActionSelect::ActionSelect(ApplicationManager* pApp) : Action(pApp) {}

void ActionSelect::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    Point P;
    pIn->GetPointClicked(P);

    // Remove old selection
    pManager->UnselectAll();

    Statement* pClicked = pManager->GetStatement(P);
    Connector *pClick = pManager->GetConnectorAtPoint(P);
    if (pClicked)
    {
        pClicked->SetSelected(true);
        pOut->PrintMessage("Statement selected.");
    }
    if (pClick)
    {
        pClicked->SetSelected(true);
        pOut->PrintMessage("connector selected.");
    }

    else
    {
        pOut->PrintMessage("No statement nor connector  clicked.");
    }
}
