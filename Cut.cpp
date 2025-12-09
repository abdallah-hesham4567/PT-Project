#include "Cut.h"
#include "..\ApplicationManager.h"
#include "..\GUI\Input.h"
#include "..\GUI\Output.h"

Cut::Cut(ApplicationManager* pAppManager) : Action(pAppManager)
{
}

void Cut::ReadActionParameters()
{
	// No parameters to read - cut operates on already selected statement
}

void Cut::Execute()
{
	// Get pointers to Output
	Output* pOut = pManager->GetOutput();

	// Get the currently selected statement
	Statement* pSelectedStat = pManager->GetSelectedStatement();

	if (pSelectedStat != nullptr)
	{
		// Step 1: Clone the selected statement for clipboard
		Statement* pClonedStat = pSelectedStat->Clone();

		// Delete old clipboard content if it exists
		Statement* pOldClipboard = pManager->GetClipboard();
		if (pOldClipboard != nullptr)
		{
			delete pOldClipboard;
		}

		// Store the cloned statement in clipboard
		pManager->SetClipboard(pClonedStat);

		// Step 2: Delete the original statement (and its connectors)
		pManager->DeleteStatement(pSelectedStat);

		// Clear the selection
		pManager->SetSelectedStatement(nullptr);

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