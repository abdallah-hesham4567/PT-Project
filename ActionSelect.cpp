#include "ActionSelect.h"

ActionSelect::ActionSelect(ApplicationManager* pApp) : Action(pApp) {}

void ActionSelect::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    pOut->PrintMessage("Ready to select.");

    Point P;
    pIn->GetPointClicked(P);

    // Remove old selection
    //pManager->UnselectAll();
    Statement* pClickedStat = pManager->GetStatement(P);
    Connector* pClickedConn = pManager->GetConnectorAtPoint(P);

    // -------- CASE 1: STATEMENT CLICKED --------
    if (pClickedStat)
    {

        // If already selected → unselect it
        if (pClickedStat->IsSelected())
        {
            
            pClickedStat->SetSelected(false);
            pManager->SetSelectedStatement(nullptr);
            pOut->PrintMessage("Statement unselected.");
        }
        else
        {

            //// Unselect everything else first
           
            pManager->UnselectAll();
            // Then select this one
            pClickedStat->SetSelected(true);
            pManager->SetSelectedStatement(pClickedStat);
            pManager->SetSelectedConnector(nullptr);
            pOut->PrintMessage("Statement selected.");
        }

        return;
    }

    // -------- CASE 2: CONNECTOR CLICKED --------
    if (pClickedConn)
    {
        if (pClickedConn->IsSelected())
        {
           // pManager->UnselectAll();
            pClickedConn->SetSelected(false);
            pManager->SetSelectedConnector(nullptr);
            pOut->PrintMessage("Connector unselected.");
        }
        else
        {
            pManager->UnselectAll();
            pClickedConn->SetSelected(true);
            pManager->SetSelectedConnector(pClickedConn);
            pManager->SetSelectedStatement(nullptr);
            pOut->PrintMessage("Connector selected.");
        }

        return;
    }

    // -------- CASE 3: CLICKED EMPTY AREA --------
   // pManager->UnselectAll();
    pOut->PrintMessage("Nothing clicked. All unselected.");
}

