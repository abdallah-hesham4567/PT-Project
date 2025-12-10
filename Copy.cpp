#include "Copy.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Copy::Copy(ApplicationManager* pApp) : Action(pApp) {}

void Copy::ReadActionParameters()
{
    // No parameters to read
}

void Copy::Execute()
{
    Output* pOut = pManager->GetOutput();

    Statement* selected = pManager->GetSelectedStatement();

    if (!selected)
    {
        pOut->PrintMessage("No statement selected to copy!");
        return;
    }

    // Clone the statement (WITHOUT connectors as required)
    Statement* copied = selected->Clone();

    // Store in clipboard
    pManager->SetClipboard(copied);

    pOut->PrintMessage("Statement copied.");
}
