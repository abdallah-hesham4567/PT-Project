#include "Paste.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

Paste::Paste(ApplicationManager* pApp) : Action(pApp)
{
}

void Paste::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

    // Get the clipboard content
    Statement* clipboard = pManager->GetClipboard();

    if (clipboard == NULL)
    {
        pOut->PrintMessage("Clipboard is empty. Nothing to paste.");
        return;
    }

    // Clone the clipboard statement
    Statement* newStat = clipboard->Clone();

    Point P;
    pOut->PrintMessage("Please click on the desired location to paste");
    pIn->GetPointClicked(P);
    //newStat->SetPosition(P);

    // Add to the application
    pManager->AddStatement(newStat);

    pOut->PrintMessage("Statement pasted successfully.");
    pManager->UpdateInterface();
}
