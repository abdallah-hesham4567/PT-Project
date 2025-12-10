#include "Cut.h"
#include "Copy.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"


Cut::Cut(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Cut::Execute()
{
	//ApplicationManager* pManager;

	// Get pointers to Output
	Output* pOut = pManager->GetOutput();

	// Get the currently selected statement
	Statement* SelectedStat = pManager->GetSelectedStatement();

	Copy copyAction(pManager);


	if (copyAction.CopyToClipboard(SelectedStat)) //copying the statement while checking if it's copied 
	{
		// Delete the original statement (and its connectors)
		pManager->DeleteStatement(SelectedStat);

		// Show success message
		pOut->PrintMessage("Statement cut to clipboard");

		// Update the interface
		pManager->UpdateInterface();
	}
	else
	{
		// No statement is selected
		pOut->PrintMessage("No statement selected. Please select a statement first.");
	}
}