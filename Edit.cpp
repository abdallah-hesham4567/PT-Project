#include "Edit.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Edit::Edit(ApplicationManager* pApp) : Action(pApp)
{
    SelectedStat = nullptr;
}

void Edit::ReadActionParameters()
{
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    pOut->PrintMessage("Click the statement you want to edit...");
    SelectedStat = pManager->GetSelectedStatement();

    if (!SelectedStat)
        pOut->PrintMessage("No statement selected!");
}

void Edit::Execute()
{
    ReadActionParameters();

    if (SelectedStat)
        SelectedStat->Edit();    // Call the overridden Edit in the statement
}
