#include "Copy.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

Copy::Copy(ApplicationManager* pApp) : Action(pApp) {}

bool Copy::CopyToClipboard(Statement* pStat)
{
    //core copying logic without any UI messages

    if (pStat == nullptr)
    {
        return false;  // Nothing to copy
    }

    // Clone the selected statement
    Statement* pClonedStat = pStat->Clone();

    // Store the cloned statement in clipboard
    pManager->SetClipboard(pClonedStat);

    return true;  // Copy successful
}

void Copy::Execute()
{
    Output* pOut = pManager->GetOutput();

	Statement* SelectedStat = pManager->GetSelectedStatement();

	if (CopyToClipboard(SelectedStat))
	{
		pOut->PrintMessage("Statement copied.");
	}
	else
	{
		pOut->PrintMessage("No Statement is selected, please select a statement to copy");
	}

    pManager->UpdateInterface();

}
