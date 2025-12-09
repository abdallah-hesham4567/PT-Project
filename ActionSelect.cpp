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

    Statement* pClicked = pManager->GetStatementAtPoint(P);

    if (pClicked)
    {
        pClicked->SetSelected(true);
        pOut->PrintMessage("Statement selected.");
    }
    else
    {
        pOut->PrintMessage("No statement clicked.");
    }
}
